#include <thread>
#include "Scene.h"

Scene::Scene(const std::string &filepath) {
    tinyxml2::XMLDocument file;
    std::stringstream stream;

    auto res = file.LoadFile(filepath.c_str());
    if (res)
    {
        throw std::runtime_error("Error: The xml file cannot be loaded.");
    }

    auto root = file.FirstChild();
    if (!root)
    {
        throw std::runtime_error("Error: Root is not found.");
    }

    //Get BackgroundColor
    auto element = root->FirstChildElement("BackgroundColor");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0 0 0" << std::endl;
    }
    stream >> this->background_color.x >> this->background_color.y >> this->background_color.z;

    //Get ShadowRayEpsilon
    element = root->FirstChildElement("ShadowRayEpsilon");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0.001" << std::endl;
    }
    stream >> this->shadow_ray_epsilon;

    //Get MaxRecursionDepth
    element = root->FirstChildElement("MaxRecursionDepth");
    if (element)
    {
        stream << element->GetText() << std::endl;
    }
    else
    {
        stream << "0" << std::endl;
    }
    stream >> max_recursion_depth;

    //Get Cameras
    element = root->FirstChildElement("Cameras");
    element = element->FirstChildElement("Camera");
    while (element)
    {
        auto *camera = new Camera();
        Vector w, v1, v2;

        auto child = element->FirstChildElement("Position");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Gaze");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Up");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("NearPlane");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("NearDistance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("ImageResolution");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("ImageName");
        stream << child->GetText() << std::endl;

        stream >> camera->e.x >> camera->e.y >> camera->e.z;
        stream >> w.x >> w.y >> w.z;
        stream >> camera->v.x >> camera->v.y >> camera->v.z;
        stream >> v1.x >> v1.y;
        stream >> v2.x >> v2.y;
        stream >> camera->distance;
        stream >> camera->width >> camera->height;
        stream >> camera->image_name;

        camera->w = w*(-1);
        camera->pixelWidth = (v1.y-v1.x) / (float) camera->width;
        camera->pixelWidthOffset = camera->pixelWidth / 2;
        camera->pixelHeight = (v2.y-v2.x) / (float) camera->height;
        camera->pixelHeightOffset = camera->pixelHeight / 2;
        camera->u = camera->v&camera->w;
        camera->m = camera->e + camera->w*(-camera->distance);
        camera->q = camera->m + camera->u*v1.x + camera->v*v2.y;

        cameras.push_back(camera);
        element = element->NextSiblingElement("Camera");
    }

    //Get Lights
    element = root->FirstChildElement("Lights");
    auto child = element->FirstChildElement("AmbientLight");
    stream << child->GetText() << std::endl;
    stream >> ambient_light.x >> ambient_light.y >> ambient_light.z;
    element = element->FirstChildElement("PointLight");
    PointLight point_light;
    while (element)
    {
        child = element->FirstChildElement("Position");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("Intensity");
        stream << child->GetText() << std::endl;

        stream >> point_light.position.x >> point_light.position.y >> point_light.position.z;
        stream >> point_light.intensity.x >> point_light.intensity.y >> point_light.intensity.z;

        point_lights.push_back(point_light);
        element = element->NextSiblingElement("PointLight");
    }

    //Get Materials
    element = root->FirstChildElement("Materials");
    element = element->FirstChildElement("Material");
    Material material;
    while (element)
    {
        material.is_mirror = (element->Attribute("type", "mirror") != NULL);

        child = element->FirstChildElement("AmbientReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("DiffuseReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("SpecularReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("MirrorReflectance");
        stream << child->GetText() << std::endl;
        child = element->FirstChildElement("PhongExponent");
        stream << child->GetText() << std::endl;

        stream >> material.ambient.x >> material.ambient.y >> material.ambient.z;
        stream >> material.diffuse.x >> material.diffuse.y >> material.diffuse.z;
        stream >> material.specular.x >> material.specular.y >> material.specular.z;
        stream >> material.mirror.x >> material.mirror.y >> material.mirror.z;
        stream >> material.phong_exponent;

        materials.push_back(material);
        element = element->NextSiblingElement("Material");
    }

    //Get VertexData
    element = root->FirstChildElement("VertexData");
    stream << element->GetText() << std::endl;
    Vector vertex;
    while (!(stream >> vertex.x).eof())
    {
        stream >> vertex.y >> vertex.z;
        vertex_data.push_back(vertex);
    }
    stream.clear();

    //Get Meshes
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Mesh");
    while (element)
    {
        int material_id, v0_id, v1_id, v2_id;
        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> material_id;
        child = element->FirstChildElement("Faces");
        stream << child->GetText() << std::endl;
        auto mesh = new Mesh(this->materials[material_id-1]);
        while (!(stream >> v0_id).eof())
        {
            stream >> v1_id >> v2_id;
            auto *triangle = new Triangle(this->materials[material_id-1],
                                          this->vertex_data[v0_id-1],
                                          this->vertex_data[v1_id-1],
                                          this->vertex_data[v2_id-1]);
            mesh->triangles.push_back(triangle);
        }
        stream.clear();
        objects.push_back(mesh);
        element = element->NextSiblingElement("Mesh");
    }
    stream.clear();

    //Get Triangles
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Triangle");
    while (element)
    {
        int material_id, v0_id, v1_id, v2_id;
        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> material_id;
        child = element->FirstChildElement("Indices");
        stream << child->GetText() << std::endl;
        stream >> v0_id >> v1_id >> v2_id;
        auto *triangle = new Triangle(this->materials[material_id-1],
                                      this->vertex_data[v0_id-1],
                                      this->vertex_data[v1_id-1],
                                      this->vertex_data[v2_id-1]);
        objects.push_back(triangle);
        element = element->NextSiblingElement("Triangle");
    }

    //Get Spheres
    element = root->FirstChildElement("Objects");
    element = element->FirstChildElement("Sphere");
    while (element)
    {
        int material_id, center_vertex_id;
        float radius;
        child = element->FirstChildElement("Material");
        stream << child->GetText() << std::endl;
        stream >> material_id;
        child = element->FirstChildElement("Center");
        stream << child->GetText() << std::endl;
        stream >> center_vertex_id;

        child = element->FirstChildElement("Radius");
        stream << child->GetText() << std::endl;
        stream >> radius;
        auto *sphere = new Sphere(this->materials[material_id-1],
                                  this->vertex_data[center_vertex_id-1],
                                  radius);
        objects.push_back(sphere);
        element = element->NextSiblingElement("Sphere");
    }
}

Scene::~Scene() {
    for(auto camera : this->cameras){
        delete camera;
    }
    for(auto object : this->objects){
        delete object;
    }
}

void Scene::renderScene() {
    for(auto camera : this->cameras) {
        auto start = std::chrono::system_clock::now();

        cCamera = camera;
        this->cImage = new unsigned char [cCamera->width * cCamera->height * 3];
        std::thread t1(&Scene::renderCamera, this, 0 , cCamera->width);
        t1.join();
        write_ppm(this->cCamera->image_name.c_str(), this->cImage, this->cCamera->width, this->cCamera->height);
        delete[] this->cImage;

        auto end = std::chrono::system_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count() << "[ms]" << std::endl;
    }
}

void Scene::renderCamera(int start, int end) {
    int index = start;
    for (int j = 0; j < cCamera->height; ++j)
    {
        for (int i = start; i < end; ++i)
        {
            Ray generatedRay = this->cCamera->generateRay(i, j);

            Vector color = this->computeColor(generatedRay, 0, nullptr);

            this->cImage[j*cCamera->width*3 + i*3] = (unsigned char)color.x;
            this->cImage[j*cCamera->width*3 + i*3+1] = (unsigned char)color.y;
            this->cImage[j*cCamera->width*3 + i*3+2] = (unsigned char)color.z;
        }
    }
}

Vector Scene::computeColor(Ray &ray, int recursionDepth, Object* recursionObject) {
    Vector color;
    float minT = MAX_T;
    Object *intersectedObject = nullptr;
    for(auto object : this->objects){
        if(recursionObject != object) {
            object->intersect(&ray, recursionObject);
            if (ray.t < minT && ray.t > this->shadow_ray_epsilon) {
                minT = ray.t;
                intersectedObject = object;
            }
        }
    }
    ray.t = minT;
    ray.p = ray.origin + ray.direction*ray.t;

    if(intersectedObject != nullptr){
        intersectedObject->normal(ray);
        Vector ambient, diffuse, specular, mirror, E;

        ambient = this->ambient_light;
        ambient *= intersectedObject->material.ambient;

        for(auto &pointLight : this->point_lights) {
            Vector lightVector = pointLight.position - ray.p;
            Vector nLightVector = !lightVector;
            bool inShadow = false;

            Ray shadowRay;
            shadowRay.origin = ray.p + ray.n*this->shadow_ray_epsilon;
            shadowRay.direction = lightVector;
            //float intersectionToLight = len(pointLight.position - (ray.p + lightVector * this->shadow_ray_epsilon));
            for (auto object: this->objects) {
                object->intersect(&shadowRay, nullptr);
                //float newIntersectionToLight = len(shadowRay.origin + shadowRay.direction*shadowRay.t - (ray.p + lightVector * this->shadow_ray_epsilon));
                if (shadowRay.t < 1 && shadowRay.t > 0) {
                    //if(newIntersectionToLight-intersectionToLight <= 0 )
                    inShadow = true;
                    break;
                }
            }

            if (!inShadow) {
                E = pointLight.intensity / (lightVector*lightVector);

                Vector h = !(nLightVector + !(ray.origin-ray.p));

                Vector kd = intersectedObject->material.diffuse;
                kd *= E * (nLightVector * ray.n);
                diffuse = nLightVector * ray.n > 0 ? diffuse + kd : diffuse;

                Vector ks = intersectedObject->material.specular;
                ks *= E * pow((h * ray.n), intersectedObject->material.phong_exponent);
                specular = h * ray.n > 0 ? specular + ks : specular;
            }
        }

        // mesh kendiile yansıma yapmıyo hepsi aynı obje olduğu için
        if(intersectedObject->material.is_mirror && recursionDepth < this->max_recursion_depth) {
            Ray wr;
            Vector wo = !(ray.origin-ray.p);
            wr.origin = ray.p;
            wr.direction = !(ray.n*(ray.n*wo)*2 - wo);
            Vector km = intersectedObject->material.mirror;
            km *= computeColor(wr, recursionDepth+1, intersectedObject->getIntersectedObject());
            mirror = mirror + km;
        }

        color = ambient + diffuse + specular + mirror;

        if(color.x > 255){
            color.x = 255;
        }
        if(color.y > 255){
            color.y = 255;
        }
        if(color.z > 255){
            color.z = 255;
        }
    } else if (recursionDepth == 0){
        color = this->background_color;
    }
    return color;
}


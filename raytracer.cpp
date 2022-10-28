#include <iostream>

#include "default_files/parser.h"
#include "default_files/ppm.h"

#include "Camera.h"
#include "Ray.h"
#include "Object.h"

Vector computeColor(Ray ray,parser::Scene scene) {
    Vector color;
    float t;
    float minT = 100;
    int intersectedSphereNumber = -1, intersectedTriangleNumber = -1, intersectedMeshesNumber = -1;
    std::vector<Sphere> spheres;
    std::vector<Triangle> triangles;
    std::vector<Mesh> meshes;

    for(auto parsedSphere : scene.spheres){
        Sphere sphere = Sphere(parsedSphere.center_vertex_id,scene.vertex_data[parsedSphere.center_vertex_id-1],
                               parsedSphere.radius,
                               parsedSphere.material_id,scene.materials[parsedSphere.material_id-1]);
        t = sphere.intersect(ray);
        spheres.push_back(sphere);
        if(t<minT && t>=1){
            minT = t;
            intersectedSphereNumber = spheres.size()-1;
        }
    }

    for(auto parsedTriangle : scene.triangles){
        Triangle triangle = Triangle(parsedTriangle.indices,scene.vertex_data,
                               parsedTriangle.material_id,scene.materials[parsedTriangle.material_id-1]);
        t = triangle.intersect(ray);
        triangles.push_back(triangle);
        if(t<minT && t>=1){
            minT = t;
            intersectedSphereNumber = -1;
            intersectedTriangleNumber = triangles.size()-1;
        }
    }

    for(auto parsedMeshes : scene.meshes){
        Mesh mesh = Mesh(parsedMeshes.faces,scene.vertex_data,
                                     parsedMeshes.material_id,scene.materials[parsedMeshes.material_id-1]);
        t = mesh.intersect(ray);
        meshes.push_back(mesh);
        if(t<minT && t>=1){
            minT = t;
            intersectedSphereNumber = -1;
            intersectedTriangleNumber = -1;
            intersectedMeshesNumber = meshes.size()-1;
        }
    }

    if(intersectedSphereNumber > -1){
        color = spheres[intersectedSphereNumber].getColor();
        for(auto pointLight : scene.point_lights){
            Vector p = ray.origin + ray.direction*minT;
            Vector l = !(Vector(pointLight.position)+p*(-1));
            Vector n = !(p-spheres[intersectedSphereNumber].centerVertex);
            if(l*n >= 0){
                color = color*(l*n);
            } else {
                color = color*(l*n);
            }
        }
    } else if(intersectedTriangleNumber > -1) {
        color = triangles[intersectedTriangleNumber].getColor();
        for(auto pointLight : scene.point_lights){
            Vector p = ray.origin + ray.direction*minT;
            Vector l = !(Vector(pointLight.position)+p*(-1));
            Vector n = !((triangles[intersectedTriangleNumber].v2-triangles[intersectedTriangleNumber].v1)&(triangles[intersectedTriangleNumber].v0-triangles[intersectedTriangleNumber].v1));
            if(l*n >= 0){
                color = color*(l*n);
            } else {
                color = color*(l*n);
            }
        }
    } else if(intersectedMeshesNumber > -1) {
        color = meshes[intersectedMeshesNumber].getColor();
        for(auto pointLight : scene.point_lights){
            Vector p = ray.origin + ray.direction*minT;
            Vector l = !(Vector(pointLight.position)+p*(-1));
            Vector n = !((meshes[intersectedMeshesNumber].v2-meshes[intersectedMeshesNumber].v1)&(meshes[intersectedMeshesNumber].v0-meshes[intersectedMeshesNumber].v1));
            if(l*n >= 0){
                color = color*(l*n);
            } else {
                color = color*(l*n);
            }
        }
    }

    if(color.x < 0 ||color.y < 0 || color.z < 0){
        color = Vector();
    }
    return color;
}

int main(int argc, char* argv[])
{
    parser::Scene scene;

    scene.loadFromXml(argv[1]);

    for(auto sceneCamera : scene.cameras){

        Camera camera(sceneCamera);

        unsigned char* image = new unsigned char [camera.width * camera.height * 3];

        int index = 0;
        for (int j = 0; j < camera.height; ++j)
        {
            for (int i = 0; i < camera.width; ++i)
            {
                Ray generatedRay = camera.generateRay(i, j);

                Vector color = computeColor(generatedRay, scene);

                image[index++] = (unsigned char)(255 * color.x);
                image[index++] = (unsigned char)(255 * color.y);
                image[index++] = (unsigned char)(255 * color.z);
            }
        }

        write_ppm(camera.image_name.c_str(), image, camera.width, camera.height);
    }
}
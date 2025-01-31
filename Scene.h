#ifndef INC_477_HW1_SCENE_H
#define INC_477_HW1_SCENE_H

#include <utility>
#include <sstream>
#include <thread>
#include <mutex>

#include "Vector.h"
#include "Camera.h"
#include "Object.h"
#include "./default_files/tinyxml2.h"
#include "./default_files/ppm.h"

class Scene {
public:
    Vector background_color;
    float shadow_ray_epsilon;
    int max_recursion_depth;
    std::vector<Camera*> cameras;
    Vector ambient_light;
    std::vector<PointLight> point_lights;
    std::vector<Material> materials;
    std::vector<Vector> vertex_data;
    std::vector<Object*> objects;

    Camera* cCamera;
    unsigned char* cImage;

    std::mutex mutex;
    int index;

    explicit Scene(const std::string &filepath);
    ~Scene();

    void renderScene();
    void renderCamera();
    void renderPixel(int, int);
    Vector computeColor(Ray&, int);
    int getRow(int&);
};

#endif //INC_477_HW1_SCENE_H
#ifndef INC_477_HW1_SCENE_H
#define INC_477_HW1_SCENE_H

#include <utility>

#include "Vector.h"
#include "Camera.h"
#include "Object.h"

class Scene {
public:
    parser::Scene scene;
    Camera *currentCamera;
    Ray *currentRay;
    std::vector<Sphere> spheres;

    Scene(parser::Scene &parsedScene);

    Vector ComputeColor();
};

#endif //INC_477_HW1_SCENE_H
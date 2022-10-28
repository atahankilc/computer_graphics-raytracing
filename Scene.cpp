#include "Scene.h"

#define MAX_T 100

Scene::Scene(parser::Scene &parsedScene) {

}

Vector Scene::ComputeColor() {
    Vector colorVector;
    float maxT = MAX_T;
    float t;

    for(auto sphere : scene.spheres){
        t = 0;
        if(t<maxT && t>= currentCamera->distance){
            maxT = t;
            colorVector = scene.materials[sphere.material_id-1].diffuse;
        }
    }
    if (maxT == MAX_T) {
        colorVector = Vector(scene.background_color) / 255;
    }
    return colorVector;
}

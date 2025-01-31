#ifndef INC_477_HW1_CAMERA_H
#define INC_477_HW1_CAMERA_H

#include <string>
#include <iostream>

#include "Vector.h"
#include "Ray.h"

class Camera {
public:
    Vector e, v, w, u, m, q;
    int width{}, height{};
    float distance{}, pixelWidth{}, pixelWidthOffset{}, pixelHeight{}, pixelHeightOffset{};
    std::string image_name;

    Camera();
    ~Camera();

    Ray generateRay(int, int) const;
};

#endif //INC_477_HW1_CAMERA_H
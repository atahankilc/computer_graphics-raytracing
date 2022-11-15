#ifndef INC_477_HW1_RAY_H
#define INC_477_HW1_RAY_H

#include "Vector.h"

struct Ray {
    Vector origin, direction;
    Vector p, n;
    float t = MAX_T;

    Ray();
    Ray(Vector const &origin, Vector const &direction);
};

#endif //INC_477_HW1_RAY_H
#ifndef INC_477_HW1_HELPERS_H
#define INC_477_HW1_HELPERS_H

#include <math.h>

#include "Vector.h"

static float det(const Vector& v1, const Vector& v2, const Vector& v3){
    float A;
    A = v1.x*(v2.y*v3.z-v3.y*v2.z) + v1.y*(v3.x*v2.z-v2.x*v3.z) + v1.z*(v2.x*v3.y-v2.y*v3.x);
    return A;
}

static float det(float a, float b, float c, float d, float e, float f, float g, float h, float i){
    float determinant;
    determinant = (a * ((e * i) - (h * f))) + (b * ((g * f) - (d * i))) + (c * ((d * h) - (e * g)));
    return determinant;
}

static float len(const Vector& v1) {
    float A;
    A = sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
    return A;
}

#endif //INC_477_HW1_HELPERS_H

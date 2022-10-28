#ifndef INC_477_HW1_HELPERS_H
#define INC_477_HW1_HELPERS_H

#include "Vector.h"

static float det(Vector v1, Vector v2, Vector v3){
    float A;
    A = v1.x*(v2.y*v3.z-v3.y*v2.z) + v1.y*(v3.x*v2.z-v2.x*v3.z) + v1.z*(v2.x*v3.y-v2.y*v3.x);
    return A;
}

#endif //INC_477_HW1_HELPERS_H

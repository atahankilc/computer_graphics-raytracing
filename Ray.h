#ifndef INC_477_HW1_RAY_H
#define INC_477_HW1_RAY_H

#include "Vector.h"

class Ray {
public:
    Vector origin, direction;

    Ray(Vector const &origin, Vector const &direction);
};

#endif //INC_477_HW1_RAY_H
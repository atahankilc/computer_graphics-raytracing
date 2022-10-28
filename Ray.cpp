#include "Ray.h"

Ray::Ray(const Vector &origin, const Vector &direction) {
    this->origin = Vector(origin);
    this->direction = Vector(direction);
}
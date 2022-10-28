#ifndef INC_477_HW1_VECTOR_H
#define INC_477_HW1_VECTOR_H

#include "additional_files/vector.h"

class Vector {
public:
    float x, y, z;

    Vector() {x = 0, y = 0, z = 0;}
    Vector(Vec3f const &obj);
    Vector(Vec3i const &obj);
    Vector(Vector const &obj);

    Vector& operator= (Vector const &obj);

    Vector operator+ (Vector const &obj) const;
    Vector operator- (Vector const &obj) const;
    Vector operator* (float magnitude) const;
    Vector operator/ (float magnitude) const;

    Vector operator! () const; // normalize
    float operator* (Vector const &obj) const; // dot product
    Vector operator& (Vector const &obj) const; // cross product
};

#endif //INC_477_HW1_VECTOR_H
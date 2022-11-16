#ifndef INC_477_HW1_VECTOR_H
#define INC_477_HW1_VECTOR_H

#include <cmath>
#include <limits>

#define MAX_T std::numeric_limits<float>::max()

typedef struct Vector {
    float x, y, z;

    Vector() {x = 0, y = 0, z = 0;}

    Vector(Vector const &str) {
        this->x = str.x;
        this->y = str.y;
        this->z = str.z;
    }

    Vector& operator= (Vector const &str) {
        this->x = str.x;
        this->y = str.y;
        this->z = str.z;
        return *this;
    }

    Vector operator+ (Vector const &str) const {
        Vector v;
        v.x = this->x + str.x;
        v.y = this->y + str.y;
        v.z = this->z + str.z;
        return v;
    }

    Vector operator- (Vector const &str) const {
        Vector v;
        v.x = this->x - str.x;
        v.y = this->y - str.y;
        v.z = this->z - str.z;
        return v;
    }

    Vector operator* (float magnitude) const {
        Vector v;
        v.x = this->x * magnitude;
        v.y = this->y * magnitude;
        v.z = this->z * magnitude;
        return v;
    }

    // color product
    void operator*= (Vector const &str) {
        this->x = this->x * str.x;
        this->y = this->y * str.y;
        this->z = this->z * str.z;
    }

    Vector operator/ (float magnitude) const {
        Vector v;
        v.x = this->x / magnitude;
        v.y = this->y / magnitude;
        v.z = this->z / magnitude;
        return v;
    }

    // normalize
    Vector operator! () const {
        Vector v;
        float length = sqrt((*this)*(*this));
        v.x = this->x/length;
        v.y = this->y/length;
        v.z = this->z/length;
        return v;
    }

    // dot product
    float operator* (Vector const &str) const {
        float f;
        f = this->x*str.x+this->y*str.y+this->z*str.z;
        return f;
    }

    // cross product
    Vector operator& (Vector const &str) const {
        Vector v;
        v.x = this->y * str.z - this->z * str.y;
        v.y = this->z * str.x - this->x * str.z;
        v.z = this->x * str.y - this->y * str.x;
        return v;
    }
} Vector;

#endif //INC_477_HW1_VECTOR_H
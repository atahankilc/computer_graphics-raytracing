/*
#include <cmath>
#include "Vector.h"

Vector::Vector(Vec3f const &str) {
    this->x = str.x;
    this->y = str.y;
    this->z = str.z;
}

Vector::Vector(Vec3i const &str) {
    this->x = float(str.x);
    this->y = float(str.y);
    this->z = float(str.z);
}

Vector::Vector(Vector const &str) {
    this->x = str.x;
    this->y = str.y;
    this->z = str.z;
}

Vector& Vector::operator=(Vector const &str) {
    this->x = str.x;
    this->y = str.y;
    this->z = str.z;
    return *this;
}

Vector Vector::operator+(Vector const &str) const {
    Vector v = Vector();
    v.x = this->x + str.x;
    v.y = this->y + str.y;
    v.z = this->z + str.z;
    return v;
}

Vector Vector::operator-(Vector const &str) const {
    Vector v = Vector();
    v.x = this->x - str.x;
    v.y = this->y - str.y;
    v.z = this->z - str.z;
    return v;
}

Vector Vector::operator*(float magnitude) const {
    Vector v = Vector();
    v.x = this->x * magnitude;
    v.y = this->y * magnitude;
    v.z = this->z * magnitude;
    return v;
}

Vector Vector::operator/(float magnitude) const {
    Vector v = Vector();
    v.x = this->x / magnitude;
    v.y = this->y / magnitude;
    v.z = this->z / magnitude;
    return v;
}

Vector Vector::operator!() const {
    Vector v = Vector();
    float length = sqrt((*this)*(*this));
    v.x = this->x/length;
    v.y = this->y/length;
    v.x = this->z/length;
    return v;
}

Vector Vector::operator&(Vector const &str) const{
    Vector v = Vector();
    v.x = this->y * str.z - this->z * str.y;
    v.y = this->z * str.x - this->x * str.z;
    v.z = this->x * str.y - this->y * str.x;
    return v;
}

float Vector::operator*(Vector const &str) const {
    float f;
    f = this->x*str.x+this->y*str.y+this->z*str.z;
    return f;
}
 */
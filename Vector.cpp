#include <cmath>
#include "Vector.h"

Vector::Vector(Vec3f const &obj) {
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
}

Vector::Vector(Vec3i const &obj) {
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
}

Vector::Vector(Vector const &obj) {
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
}

Vector& Vector::operator=(Vector const &obj) {
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
    return *this;
}

Vector Vector::operator+(Vector const &obj) const {
    Vector v = Vector();
    v.x = this->x + obj.x;
    v.y = this->y + obj.y;
    v.z = this->z + obj.z;
    return v;
}

Vector Vector::operator-(Vector const &obj) const {
    Vector v = Vector();
    v.x = this->x - obj.x;
    v.y = this->y - obj.y;
    v.z = this->z - obj.z;
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

Vector Vector::operator&(Vector const &obj) const{
    Vector v = Vector();
    v.x = this->y * obj.z - this->z * obj.y;
    v.y = this->z * obj.x - this->x * obj.z;
    v.z = this->x * obj.y - this->y * obj.x;
    return v;
}

float Vector::operator*(Vector const &obj) const {
    float f;
    f = this->x*obj.x+this->y*obj.y+this->z*obj.z;
    return f;
}
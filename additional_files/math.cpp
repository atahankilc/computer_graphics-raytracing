#include "math.h"

using namespace math;

Vec3f math::Vec3fCopy(const Vec3f& v1){
    Vec3f v;
    v.x = v1.x;
    v.y = v1.y;
    v.z = v1.z;
    return v;
}

Vec3f math::Vec3fNormalization(const Vec3f& v1){
    float length = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    Vec3f v;
    v.x = v1.x / length;
    v.y = v1.y / length;
    v.z = v1.z / length;
    return v;
}

Vec3f math::Vec3fCrossProduct(const Vec3f& v1, const Vec3f& v2){
    Vec3f v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}


Vec3f math::Vec3fAddition(const Vec3f& v1, const Vec3f& v2){
    Vec3f v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    return v;
};

Vec3f math::Vec3fScalarMultiplication(const Vec3f& v1, float magnitude){

    Vec3f v;
    v.x = v1.x * magnitude;
    v.y = v1.y * magnitude;
    v.z = v1.z * magnitude;
    return v;
};

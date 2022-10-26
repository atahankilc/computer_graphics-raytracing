#ifndef __HW1__MATH__
#define __HW1__MATH__

#include <cmath>

#include "vector.h"

namespace math {
    Vec3f Vec3fCopy(const Vec3f& v1);
    
    Vec3f Vec3fNormalization(const Vec3f& v1);

    Vec3f Vec3fAddition(const Vec3f& v1, const Vec3f& v2);

    Vec3f Vec3fScalarMultiplication(const Vec3f& v1, float magnitude);

    Vec3f Vec3fCrossProduct(const Vec3f& v1, const Vec3f& v2);
}

#endif
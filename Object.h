#ifndef INC_477_HW1_OBJECT_H
#define INC_477_HW1_OBJECT_H

#include <cmath>
#include <iostream>
#include <vector>

#include "Vector.h"
#include "Ray.h"
#include "helpers.h"

struct Material
{
    bool is_mirror;
    Vector ambient;
    Vector diffuse;
    Vector specular;
    Vector mirror;
    float phong_exponent;
};

struct PointLight
{
    Vector position;
    Vector intensity;
};

class Object {
public:
    Material material;
    Object* intersectedObject;
    Vector n;

    virtual ~Object();

    virtual void intersect(Ray* ray, Object*) = 0;
    virtual void normal(Ray &ray) = 0;
    virtual Object* getIntersectedObject() = 0;
};

class Sphere : public Object {
public:
    Vector centerVertex;
    float radius;

    Sphere(Material&, Vector&, float);
    ~Sphere() override;

    void intersect(Ray*, Object*) override;
    void normal(Ray&) override;
    Object* getIntersectedObject() override;
};

class Triangle : public Object {
public:
    Vector v0, v1, v2;

    Triangle(Material&, Vector&, Vector&, Vector&);
    ~Triangle() override;

    void intersect(Ray*, Object*) override;
    void normal(Ray&) override;
    Object* getIntersectedObject() override;
};

class Mesh : public  Object {
public:
    std::vector<Triangle*> triangles;

    Mesh(Material&);
    ~Mesh() override;

    void intersect(Ray*, Object*) override;
    void normal(Ray&) override;
    Object* getIntersectedObject() override;
};

#endif //INC_477_HW1_OBJECT_H

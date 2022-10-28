#ifndef INC_477_HW1_OBJECT_H
#define INC_477_HW1_OBJECT_H

#include <cmath>

#include "Vector.h"
#include "Ray.h"
#include "default_files/parser.h"
#include "helpers.h"

class Object {
public:
    int materialId;
    parser::Material material;

    Object(int, parser::Material);

    virtual float intersect(Ray ray) = 0;
    virtual Vector getColor() = 0;
};

class Sphere : public Object {
public:
    int centerVertexId;
    Vector centerVertex;
    float radius;

    Sphere(int, Vec3f, float, int, parser::Material);

    float intersect(Ray ray) override;
    Vector getColor() override;
};

class Triangle : public Object {
public:
    parser::Face face;
    Vector v0, v1, v2;

    Triangle(parser::Face, std::vector<Vec3f>, int, parser::Material);

    float intersect(Ray ray) override;
    Vector getColor() override;
};

class Mesh : public  Object {
public:
    std::vector<Triangle> triangles;
    Vector v0, v1, v2;

    Mesh(std::vector<parser::Face>, std::vector<Vec3f>, int, parser::Material);

    float intersect(Ray ray) override;
    Vector getColor() override;
};

#endif //INC_477_HW1_OBJECT_H

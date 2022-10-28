#include "Object.h"

Object::Object(int materialId, parser::Material material) {
    this->materialId = materialId;
    this->material = material;
}

Sphere::Sphere(int centerVertexId, Vec3f centerVertex, float radius, int materialId, parser::Material material): Object(materialId, material){
    this->centerVertexId = centerVertexId;
    this->centerVertex = centerVertex;
    this->radius = radius;
}

float Sphere::intersect(Ray ray) {
    float t, t1, t2;
    float A,B,C;
    float delta;

    C = (ray.origin-this->centerVertex)*(ray.origin-this->centerVertex) - this->radius*this->radius;
    B = (ray.direction*(ray.origin-this->centerVertex))*2;
    A = ray.direction*ray.direction;

    delta = B*B-4*A*C;

    if(delta<0) {
        return -1;
    } else if (delta == 0) {
        t = -B / (2*A);
    } else {
        delta = sqrt(delta);
        t1 = (-B + delta) / (2*A);
        t2 = (-B - delta) / (2*A);
        t = t1 < t2 ? t1 : t2;
    }

    return t;
}

Vector Sphere::getColor() {
    // TODO
    return this->material.diffuse;
}

Triangle::Triangle(parser::Face face, std::vector<Vec3f> vertexData, int materialId, parser::Material material) : Object(materialId, material) {
    this->face = face;
    this->v0 = vertexData[face.v0_id-1];
    this->v1 = vertexData[face.v1_id-1];
    this->v2 = vertexData[face.v2_id-1];
}

float Triangle::intersect(Ray ray) {
    float A, alpha, beta, t;

    A = det(this->v0-this->v1,this->v0-this->v2,ray.direction);
    alpha = det(this->v0-this->v1,this->v0-ray.origin,ray.direction) / A;
    beta = det(this->v0-ray.origin,this->v0-this->v2,ray.direction) / A;
    t = det(this->v0-this->v1,this->v0-this->v2,this->v0-ray.origin) / A;

    if(alpha + beta <= 1 && alpha >= 0 && beta >= 0) {
        return t;
    } else {
        return -1;
    }
}

Vector Triangle::getColor() {
    // TODO
    return this->material.diffuse;
}

Mesh::Mesh(std::vector<parser::Face> faces, std::vector<Vec3f> vertexData, int materialId, parser::Material material) : Object(materialId, material) {
    for(auto face : faces){
        triangles.push_back(Triangle(face, vertexData, materialId, material));
    }
}

float Mesh::intersect(Ray ray) {
    float t, minT;

    for(auto triangle : this->triangles){
        t = triangle.intersect(ray);
        if(t != -1 && t < minT) {
            minT = t;
            this->v0 = triangle.v0;
            this->v1 = triangle.v1;
            this->v2 = triangle.v2;
        }
    }

    return minT;
}

Vector Mesh::getColor() {
    return this->material.diffuse;
}

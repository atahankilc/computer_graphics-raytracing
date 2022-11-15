#include "Object.h"

Object::~Object() = default;

Sphere::Sphere(Material &material, Vector &centerVertex, float radius) {
    this->material = material;
    this->centerVertex = centerVertex;
    this->radius = radius;
    this->intersectedObject = this;
}

void Sphere::intersect(Ray* ray, Object* recursionObject) {
    if(recursionObject == this) {
        ray->t = MAX_T;
        return;
    }
    float t, t1, t2;
    float A,B,C;
    float delta;

    C = (ray->origin-this->centerVertex)*(ray->origin-this->centerVertex) - this->radius*this->radius;
    B = (ray->direction*(ray->origin-this->centerVertex))*2;
    A = ray->direction*ray->direction;

    delta = B*B-4*A*C;

    if(delta<0) {
        t = -1;
    } else if (delta == 0) {
        t = -B / (2*A);
    } else {
        delta = sqrt(delta);
        t1 = (-B + delta) /  (2.f*A);
        t2 = (-B - delta) / (2.f*A);
        t = t1 < t2 ? t1 : t2;
    }

    ray->t = t;
}

void Sphere::normal(Ray &ray) {
    ray.n = !(ray.p-this->centerVertex);
}

Object *Sphere::getIntersectedObject() {
    return this->intersectedObject;
}

Sphere::~Sphere() {
    //std::cout << "sphere destructed\n";
}

Triangle::Triangle(Material &material, Vector &v0, Vector &v1, Vector &v2) {
    this->material = material;
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    this->n = !((this->v2-this->v1)&(this->v0-this->v1));
    this->intersectedObject = this;
}

void Triangle::intersect(Ray* ray, Object* recursionObject) {
    if(recursionObject == this) {
        ray->t = MAX_T;
        return;
    }

    float A, alpha, beta, t;

    A = det(this->v0.x-this->v1.x,this->v0.y-this->v1.y,this->v0.z-this->v1.z,
            this->v0.x-this->v2.x,this->v0.y-this->v2.y,this->v0.z-this->v2.z,
            ray->direction.x, ray->direction.y, ray->direction.z);
    beta = det(this->v0.x-ray->origin.x,this->v0.y-ray->origin.y,this->v0.z-ray->origin.z,
               this->v0.x-this->v2.x,this->v0.y-this->v2.y,this->v0.z-this->v2.z,
               ray->direction.x, ray->direction.y, ray->direction.z) / A;
    alpha = det(this->v0.x-this->v1.x,this->v0.y-this->v1.y,this->v0.z-this->v1.z,
                this->v0.x-ray->origin.x,this->v0.y-ray->origin.y,this->v0.z-ray->origin.z,
                ray->direction.x, ray->direction.y, ray->direction.z) / A;
    t = det(this->v0.x-this->v1.x,this->v0.y-this->v1.y,this->v0.z-this->v1.z,
            this->v0.x-this->v2.x,this->v0.y-this->v2.y,this->v0.z-this->v2.z,
            this->v0.x-ray->origin.x,this->v0.y-ray->origin.y,this->v0.z-ray->origin.z) / A;

    if(t>= 0 && t<= MAX_T && alpha + beta <= 1 && alpha >= 0 && beta >= 0) {
        ray->t = t;
    } else {
        ray->t = -1;
    }
}

void Triangle::normal(Ray &ray) {
    ray.n = this->n;
}

Object *Triangle::getIntersectedObject() {
    return this->intersectedObject;
}

Triangle::~Triangle() {
    //std::cout << "triangle destructed\n";
}

Mesh::Mesh(Material &material) {
    this->material = material;
    this->intersectedObject = this;
}

void Mesh::intersect(Ray* ray, Object* recursionObject) {
    float minT = MAX_T;

    for(auto triangle : this->triangles){
        triangle->intersect(ray, recursionObject);
        if(ray->t != -1 && ray->t < minT) {
            minT = ray->t;
            this->n = triangle->n;
            this->intersectedObject = triangle->getIntersectedObject();
        }
    }
    ray->t = minT;
}

void Mesh::normal(Ray &ray) {
    ray.n = this->n;
}

Object *Mesh::getIntersectedObject() {
    return this->intersectedObject;
}

Mesh::~Mesh() {
    for(auto triangle : this->triangles)
        delete triangle;
    //std::cout << "mesh destructed\n";
}



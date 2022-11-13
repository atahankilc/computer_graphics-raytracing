#include "Camera.h"

Camera::Camera() = default;

Camera::~Camera() {
    //std::cout << "Camera deleted\n";
}


Ray Camera::generateRay(int i, int j) const {
    float su = (float) i * this->pixelWidth + this->pixelWidthOffset;
    float sv = (float)j * this->pixelHeight + this->pixelHeightOffset;
    Vector s = this->q + this->u * su - this->v * sv;
    return Ray(this->e, s- this->e);
}
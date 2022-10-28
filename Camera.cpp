#include "Camera.h"

Camera::Camera(parser::Camera &parserCamera) {
    this->image_name = parserCamera.image_name;

    this->e = Vector(parserCamera.position);
    this->v = Vector(parserCamera.up);
    this->w = Vector(parserCamera.gaze)*(-1);
    this->u = Vector(v&w);

    this->distance = parserCamera.near_distance;
    this->width = parserCamera.image_width;
    this->height = parserCamera.image_height;

    this->pixelWidth = (parserCamera.near_plane.y-parserCamera.near_plane.x) / (float) this->width;
    this->pixelWidthOffset = this->pixelWidth / 2;
    this->pixelHeight = (parserCamera.near_plane.w-parserCamera.near_plane.z) / (float) this->height;
    this->pixelHeightOffset = this->pixelHeight / 2;

    this->m = this->e + this->w*(-this->distance);
    this->q = this->m + this->u*parserCamera.near_plane.x + this->v*parserCamera.near_plane.w;
}

Ray Camera::generateRay(int i, int j) const {
    float su = (float) i * this->pixelWidth + this->pixelWidthOffset;
    float sv = (float)j * this->pixelHeight + this->pixelHeightOffset;
    Vector s = this->q + this->u * su - this->v * sv;
    return Ray(this->e, s- this->e);
}
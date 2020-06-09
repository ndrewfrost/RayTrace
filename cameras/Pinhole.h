/*
 * pinhole.h
 * Andrew Frost
 * December 2019
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "..//core/camera.h"

class Pinhole : public Camera {
public:
    Pinhole(int width, int height, int fov, vec3f location, vec3f look);
    ~Pinhole() {};

    void printCamera();

    void getOriginDirection();
};

#endif // !PINHOLE_H_

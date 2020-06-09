/*
 * camera.h
 * Andrew Frost
 * December 2019
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>
#include "..//math/geometry.h"
#include "../cameras/pinhole.h"
//#include "../cameras/thinlens.h"

#include "rapidjson/document.h"
using namespace rapidjson;

class Camera {
public:
    Camera() {};
    virtual ~Camera() {};

    void lookMatrix();

    static Camera* createCamera(Value& cameraSpecs);

    virtual void printCamera() = 0;
    
protected:
    int height, width, fov;

    vec3f location;
    vec3f lookAt;

    Matrix44f cameraToWorld;

};


#endif // !CAMERA_H_

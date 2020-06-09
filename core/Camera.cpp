/*
 * camera.cpp
 * Andrew Frost
 * December 2019
 *
 */

#include "camera.h"

void Camera::lookMatrix() {
    vec3f dir = (location - lookAt).normalize();

    //vec3f(0,1,0) is up vector
    vec3f right = (vec3f(0, 1, 0).crossProduct(dir)).normalize();

    vec3f up = dir.crossProduct(right);

    cameraToWorld[3][0] = location.x;
    cameraToWorld[3][1] = location.y;
    cameraToWorld[3][2] = location.z;

    cameraToWorld[0][0] = right.x;
    cameraToWorld[0][1] = right.y;
    cameraToWorld[0][2] = right.z;

    cameraToWorld[1][0] = up.x;
    cameraToWorld[1][1] = up.y;
    cameraToWorld[1][2] = up.z;

    cameraToWorld[2][0] = dir.x;
    cameraToWorld[2][1] = dir.y;
    cameraToWorld[2][2] = dir.z;

    cameraToWorld[0][3] = 0;
    cameraToWorld[1][3] = 0;
    cameraToWorld[2][3] = 0;
    cameraToWorld[3][3] = 1;
}

Camera* Camera::createCamera(Value& cameraSpecs)
{
    // check if defined cameratype
    if (!cameraSpecs.HasMember("type")) {
        std::cerr << "Camera type not specified" << std::endl;
        exit(-1);
    }

    const char* cameraType = cameraSpecs["type"].GetString();

    if (strcmp(cameraType, "pinhole") == 0) {
        return new Pinhole(cameraSpecs["width"].GetInt(),
            cameraSpecs["height"].GetInt(),
            cameraSpecs["fov"].GetInt(),
            vec3f(cameraSpecs["location"][0].GetFloat(), cameraSpecs["location"][1].GetFloat(), cameraSpecs["location"][2].GetFloat()),
            vec3f(cameraSpecs["look"][0].GetFloat(), cameraSpecs["look"][1].GetFloat(), cameraSpecs["look"][2].GetFloat()));

    }
    else if (strcmp(cameraType, "thinlens") == 0) {

    }
    else {
        std::cerr << "Camera type can either be: [pinhole] or [thinlens]" << std::endl;
        exit(-1);
    }
}

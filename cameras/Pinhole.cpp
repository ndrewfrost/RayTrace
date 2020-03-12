/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"



namespace rt {

    //
    // Pinhole constructor
    //
    Pinhole::Pinhole(int width, int height, int fov, Vec3f(location), Vec3f(lookAt)) : Camera(width, height, fov, location, lookAt) {
        lookMatrix();
    }

    /**
     * Prints camera data
     * this function implements the abstract function of the base Camera class
     */
    void Pinhole::printCamera() {
        printf("I am a pinhole camera! \n");
        printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
    }

    void Pinhole::getOriginDirection(float& pixelX, float& pixelY, Vec3f& origin, Vec3f& direction, Vec2i& sample, Vec2i& samplingSize)
    {
        origin = Vec3f();
        cameraToWorld.multDirMatrix(Vec3f(pixelX, pixelY, -1), origin);
        origin.normalize();
        origin = location - origin;
        direction = -(origin - location).normalize();
    }



} //namespace rt


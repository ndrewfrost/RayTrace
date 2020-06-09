/*
 * ThinLens.cpp
 *
 *
 */
#include <iostream>


#include "ThinLens.h"




namespace rt {

    //
    // ThinLens constructor (example)
    //

    ThinLens::ThinLens(int width, int height, int fov, Vec3f(location), Vec3f(lookAt), float aperture, float focus) : Camera(width, height, fov, location, lookAt) {
        lookMatrix();
        radius = aperture / 2;
        lensNormal = lookAt - location;
        focalDistance = focus;
    }

    /**
     * Prints camera data
     * this function implements the abstract function of the base Camera class
     */
    void ThinLens::printCamera() {
        printf("I am a thin lens camera! \n");
        printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
    }

    // Random origin on lens plane within lens radius
    void ThinLens::randomOrigin(Vec3f& origin)
    {
        //Point on lens plane parallel to images
        float randomInt = randomMath::random(0, 1);
        Vec3f v(randomInt, randomInt, randomInt);
        while (lensNormal.dotProduct(v) == 1) {
            randomInt = randomMath::random(0, 1);
            v = Vec3f(randomInt, randomInt, randomInt);
        }
        v = lensNormal.dotProduct(v);

        const double PI = 3.141592653589793;

        float theta = randomMath::random(0, PI * 2);

        Vec3f p;
        p[0] = lensNormal[0] * (lensNormal[0] * v[0] + lensNormal[1] * v[1] + lensNormal[2] * v[2]) * (1 - cos(theta)) + v[0] * cos(theta) + ((-1) * lensNormal[2] * v[1] + lensNormal[1] * v[2]) * sin(theta);
        p[1] = lensNormal[1] * (lensNormal[0] * v[0] + lensNormal[1] * v[1] + lensNormal[2] * v[2]) * (1 - cos(theta)) + v[1] * cos(theta) + (lensNormal[2] * v[0] - lensNormal[0] * v[2]) * sin(theta);
        p[2] = lensNormal[2] * (lensNormal[0] * v[0] + lensNormal[1] * v[1] + lensNormal[2] * v[2]) * (1 - cos(theta)) + v[2] * cos(theta) + ((-1) * lensNormal[1] * v[0] + lensNormal[0] * v[1]) * sin(theta);

        float r = randomMath::random(0, radius);
        p = r * p.normalize();
        origin = p + origin;
    }

    // jittered origin on lens plane within lens radius
    void ThinLens::jitteredOrigin(Vec3f& origin, Vec2i& sampling, Vec2i& samplingSize)
    {
        //Point on lens plane parallel to images
        float randomInt = randomMath::random(0, 1);
        Vec3f v(randomInt, randomInt, randomInt);
        while (lensNormal.dotProduct(v) == 1) {
            randomInt = randomMath::random(0, 1);
            v = Vec3f(randomInt, randomInt, randomInt);
        }
        v = lensNormal.dotProduct(v);

        const double PI = 3.141592653589793;

        float theta = randomMath::random(sampling.x, (samplingSize.x / (samplingSize.x * samplingSize.y)) * PI * 2);

        Vec3f p;
        p[0] = lensNormal[0] * (lensNormal[0] * v[0] + lensNormal[1] * v[1] + lensNormal[2] * v[2]) * (1 - cos(theta)) + v[0] * cos(theta) + ((-1) * lensNormal[2] * v[1] + lensNormal[1] * v[2]) * sin(theta);
        p[1] = lensNormal[1] * (lensNormal[0] * v[0] + lensNormal[1] * v[1] + lensNormal[2] * v[2]) * (1 - cos(theta)) + v[1] * cos(theta) + (lensNormal[2] * v[0] - lensNormal[0] * v[2]) * sin(theta);
        p[2] = lensNormal[2] * (lensNormal[0] * v[0] + lensNormal[1] * v[1] + lensNormal[2] * v[2]) * (1 - cos(theta)) + v[2] * cos(theta) + ((-1) * lensNormal[1] * v[0] + lensNormal[0] * v[1]) * sin(theta);

        float r = randomMath::random(sampling.y, (samplingSize.y / (samplingSize.y * samplingSize.x)) * radius);
        p = r * p.normalize();
        origin = p + origin;
    }

    void ThinLens::getFocalIntersection(Vec3f& origin, Vec3f& direction, Vec2i& sampling, Vec2i& samplingSize) {
        //Where ray intersects focal plane
        Vec3f pointHit = origin + direction * focalDistance;
        // random point on aperture
        if (sampling.x == -1) {
            randomOrigin(origin);
        }
        else {
            jitteredOrigin(origin, sampling, samplingSize);
        }
        //aperture to point hit
        direction = (pointHit - origin).normalize();
    }

    void ThinLens::getOriginDirection(float& pixelX, float& pixelY, Vec3f& origin, Vec3f& direction, Vec2i& sampling, Vec2i& samplingSize)
    {
        origin = Vec3f();
        cameraToWorld.multDirMatrix(Vec3f(pixelX, pixelY, -1), origin);
        origin.normalize();
        origin = location - origin;
        direction = -(origin - location).normalize();

        getFocalIntersection(origin, direction, sampling, samplingSize);
    }

} //namespace rt

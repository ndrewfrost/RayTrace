/*
 * ThinLens.h
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"
#include <random>
#include <iostream>


namespace rt {

    class ThinLens :public Camera {
    public:

        //
        // Constructors
        //

        ThinLens(int width, int height, int fov, Vec3f(location), Vec3f(lookAt), float aperture, float focal);

        //
        //Destructor
        //
        ~ThinLens() {};

        //
        // print function (implementing abstract function of base class)
        //
        void printCamera();

        // Random Sampling for lens
        void randomOrigin(Vec3f& direction);
        void jitteredOrigin(Vec3f& origin, Vec2i& sampling, Vec2i& samplingSize);
        void getFocalIntersection(Vec3f& origin, Vec3f& direction, Vec2i& sampling, Vec2i& samplingSize);
        void getOriginDirection(float& pixelX, float& pixelY, Vec3f& origin, Vec3f& direction, Vec2i& sampling, Vec2i& samplingSize);


    private:
        float radius;
        Vec3f lensNormal;
        float focalDistance;
    };



} //namespace rt




#endif /* THINLENS_H_ */

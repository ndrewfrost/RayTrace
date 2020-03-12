/* Pinhole.h
*
*
*/

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"

namespace rt {

    class Pinhole :public Camera {
    public:

        //
        // Constructors
        //
        Pinhole(int width, int height, int fov, Vec3f(location), Vec3f(look));

        //
        //Destructor
        //
        ~Pinhole() {};

        //
        // print function (implementing abstract function of base class)
        //
        void printCamera();

        void getOriginDirection(float& pixelX, float& pixelY, Vec3f& origin, Vec3f& direction, Vec2i& sample, Vec2i& samplingSize);
    };



} //namespace rt




#endif /* PINHOLE_H_ */

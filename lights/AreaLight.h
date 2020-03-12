/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "core/LightSource.h"
#include <random>
#include <iostream>

namespace rt {

    class AreaLight :public LightSource {
    public:
        //Give light to a shape
        AreaLight(Vec3f position, Vec3f color, float intensity, Shape* sh, std::string s, int ss) : LightSource(position, intensity, color) {
            shape = sh;
            sampling = s;
            samples = ss;
        };

        ~AreaLight() {};

        bool isAreaLight() const {
            return true;
        }

        int getSamples() { return samples; };

        std::string getSampling() { return sampling; };

        Shape* getAreaLight() const {
            return shape;
        }

        void setSamples(int s) {
            samples = s;
        }

    private:
        Shape* shape;
        std::string sampling;
        int samples;
       // Vec3f randomDirection(Vec3f direction, float spread);
    };



} //namespace rt




#endif /* AREALIGHT_H_ */

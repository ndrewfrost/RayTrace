/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"

namespace rt{

class PointLight: public LightSource{
public:
    PointLight(Vec3f position, Vec3f color, float intensity) : LightSource(position, intensity, color) {};
    ~PointLight() {};


private:

};



} //namespace rt




#endif /* POINTLIGHT_H_ */

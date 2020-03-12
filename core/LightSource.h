/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_


#include "math/geometry.h"
#include "core/Shape.h"

namespace rt {

    class LightSource {
    public:
        LightSource() {};
        LightSource(Vec3f position, float intensity, Vec3f color) :position(position), intensity(intensity), color(color) {};

        Vec3f getPosition() const {
            return position;
        }

        float getIntensity() const {
            return intensity;
        }

        Vec3f getColor() const {
            return color;
        }

        virtual bool isAreaLight() const {
            return false;
        }

        virtual Shape* getAreaLight() const {
            return nullptr;
        }

        virtual int getSamples() { return 1; }

        virtual void setSamples(int s) {};

        virtual std::string getSampling() { return ""; }

    protected:
        Vec3f position;
        float intensity;
        Vec3f color;
    };

} //namespace rt


#endif /* LIGHTSOURCE_H_ */
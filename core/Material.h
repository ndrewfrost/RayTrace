/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "math/geometry.h"

namespace rt {

    class Material {
    public:
        Material() {};
        Material(float ks, float kd, float kr, float specularExponent, Vec3f diffuseColor) :
            ks(ks), kd(kd), kr(kr), specularExponent(specularExponent), diffuseColor(diffuseColor) {};

        ~Material() {};

        virtual float getReflective() const {
            return kr;
        }
        
    protected:
        float ks;
        float kd, kr;

        float specularExponent;
        Vec3f diffuseColor;
    };


} //namespace rt



#endif /* MATERIAL_H_ */

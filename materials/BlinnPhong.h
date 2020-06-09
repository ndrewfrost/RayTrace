/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core\Material.h"
#include <vector>
#include <cstdio>
#include <cmath>


namespace rt {

    class BlinnPhong : public Material {
    public:
        BlinnPhong() {};
        BlinnPhong(float ks, float kd, float kr, float specularExponent, Vec3f diffuseColor) :
            Material(ks, kd, kr, specularExponent, diffuseColor) {};
        ~BlinnPhong() {};

        Vec3f getAmbient();
        Vec3f getAmbient(Vec3f& color);

        Vec3f getSpecular(Vec3f& halfAngle, Vec3f& surfaceNormal, Vec3f& lightColor, float intensity, float& distance);
        // No texture Diffuse
        Vec3f getDiffuse(Vec3f& lightDirection, Vec3f& surfaceNormal, Vec3f& lightColor, float intensity, float& distance);
        // TExture Diffuse
        Vec3f getDiffuse(Vec3f& lightDirection, Vec3f& surfaceNormal, Vec3f& color, Vec3f& lightColor, float intensity, float& distance);


    private:
        const double PI = 3.141592653589793;
    };


} //namespace rt



#endif /* BLINNPHONG_H_ */

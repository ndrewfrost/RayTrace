/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"

namespace rt {
    Vec3f BlinnPhong::getAmbient() {
        return 0.08 * diffuseColor;
    }

    Vec3f BlinnPhong::getAmbient(Vec3f& color) {
        return 0.08 * color;
    }

    Vec3f BlinnPhong::getDiffuse(Vec3f& lightDirection, Vec3f& surfaceNormal, Vec3f& lightColor, float intensity, float& distance) {
        float diffuse = lightDirection.dotProduct(surfaceNormal);
        if (diffuse < 0) diffuse = 0.0;

        Vec3f light;
        light.x = lightColor.x / (4 * PI * distance);
        light.y = lightColor.y / (4 * PI * distance);
        light.z = lightColor.z / (4 * PI * distance);

        return kd * diffuse * diffuseColor * light * intensity;
    }

    Vec3f BlinnPhong::getDiffuse(Vec3f& lightDirection, Vec3f& surfaceNormal, Vec3f& color, Vec3f& lightColor, float intensity, float& distance) {
        float diffuse = (lightDirection).dotProduct(surfaceNormal);
        if (diffuse < 0) diffuse = 0.0;

        Vec3f light;
        light.x = lightColor.x / (4 * PI * distance);
        light.y = lightColor.y / (4 * PI * distance);
        light.z = lightColor.z / (4 * PI * distance);

        return kd * diffuse * color * light * intensity;
    }

    Vec3f BlinnPhong::getSpecular(Vec3f& halfAngle, Vec3f& surfaceNormal, Vec3f& lightColor, float intensity, float& distance) {
        float specAngle = halfAngle.dotProduct(surfaceNormal);
        if (specAngle < 0) specAngle = 0;

        Vec3f light;
        light.x = lightColor.x / (4 * PI * distance);
        light.y = lightColor.y / (4 * PI * distance);
        light.z = lightColor.z / (4 * PI * distance);

        return ks * pow(specAngle, specularExponent) * light * intensity;
    }


} //namespace rt

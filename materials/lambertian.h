/*
 * lambertian.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "../core/material.h"

 ///////////////////////////////////////////////////////////////////////////
 // Lambertian                                                            //
 ///////////////////////////////////////////////////////////////////////////

class Lambertian : public Material
{
public:
    Lambertian(glm::vec3 color) : Material(color) {}

    ~Lambertian() = default;

    virtual bool scatter(const Ray& rayIn, Ray& rayOut,
        glm::vec3& attenuation, const HitRecord& hitRecord) const
    {
        glm::vec3 dirOut = hitRecord.normal + rndPointUnitSphere();
        rayOut = Ray(hitRecord.point, dirOut);
        attenuation = m_diffuseColor;
        return true;
    }

};

#endif // !LAMBERTIAN_H_

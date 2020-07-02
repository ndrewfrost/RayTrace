/*
 * lambertian.h
 * Andrew Frost
 * 2020
 *
 

#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "../core/material.h"

///////////////////////////////////////////////////////////////////////////
// Lambertian                                                            //
///////////////////////////////////////////////////////////////////////////

class Lambertian : public Material
{
public:
    Lambertian(glm::vec3 color) : m_diffuseColor(color) {}

    ~Lambertian() = default;

    virtual bool sample(const Ray& rayIn, Ray& rayOut, 
                         const HitRecord& hitRecord) const
    {
        glm::vec3 dirOut = hitRecord.normal + rndPointHemisphere();
        rayOut = Ray(hitRecord.point, dirOut);
        return true;
    }

    virtual float pdf(const Ray& rayIn, const Ray& rayOut) const
    {
        return  1 / (2 * PI);
    }

    virtual glm::vec3 brdf(const HitRecord& record)
    {
        glm::vec3 BRDF = m_diffuseColor / PI;
    }

private:
    glm::vec3 m_diffuseColor;

};

#endif // !LAMBERTIAN_H_
*/
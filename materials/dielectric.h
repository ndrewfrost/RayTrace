/*
 * dielectric.h
 * Andrew Frost
 * 2020
 *
 

#ifndef DIELECTRIC_H_
#define DIELECTRIC_H_

#include "../core/material.h"

///////////////////////////////////////////////////////////////////////////
// Dielectric                                                            //
///////////////////////////////////////////////////////////////////////////


class Dielectric : public Material
{
public:
    Dielectric(float ri) : m_refractionIdx(ri) {}

    ~Dielectric() = default;

    virtual bool sample(const Ray& rayIn, Ray& rayOut,
                         const HitRecord& hitRecord) const
    {
        //attenuation = glm::vec3(1.0f, 1.0f, 1.0f);
        float eta = hitRecord.frontFace ? (1.0f / m_refractionIdx) : m_refractionIdx;
        
        glm::vec3 unitDir = glm::normalize(rayIn.direction());

        float cosTheta = fmin(glm::dot(-unitDir, hitRecord.normal), 1.0f);
        float sinTheta = sqrtf(1.0f - sqr(cosTheta));

        if (eta * sinTheta > 1.0f) {
            glm::vec3 reflected = glm::reflect(unitDir, hitRecord.normal);
            rayOut = Ray(hitRecord.point, reflected);
            return true;
        }

        // Schlick Approximation
        float r0 = (1.0f - m_refractionIdx) / (1.0f + m_refractionIdx);
        r0 = sqr(r0);
        float reflectProb = r0 + (1.0f - r0) * powf((1.0f - cosTheta), 5);

        if (randomFloat() < reflectProb) {
            glm::vec3 reflected = glm::reflect(unitDir, hitRecord.normal);
            rayOut = Ray(hitRecord.point, reflected);
            return true;
        }            

        glm::vec3 refracted = glm::refract(unitDir, hitRecord.normal, eta);
        rayOut = Ray(hitRecord.point, refracted);
        return true;
    }

private:
    float m_refractionIdx;
};

#endif // !DIELECTRIC_H_
*/
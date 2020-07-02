/*
 * material.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "ray.h"
#include "../common/math.h"

///////////////////////////////////////////////////////////////////////////
// Material                                                              //
///////////////////////////////////////////////////////////////////////////

class Material
{
public:
    Material() {}

    virtual ~Material() = default;

    //---------------------------------------------------------------------
    //
    //
    virtual glm::vec3 f(const Ray& rayIn, Ray& rayOut,
        const HitRecord& hitRecord) const = 0;

    //---------------------------------------------------------------------
    //
    //
    virtual glm::vec3 sample(const Ray& rayIn, Ray& rayOut,
                             const HitRecord& hitRecord) const
    {
        glm::vec3 dirOut = rndPointHemisphere(hitRecord.normal);
        rayOut = Ray(hitRecord.point, dirOut);

        return f(rayIn, rayOut, hitRecord);
    }

    //---------------------------------------------------------------------
    // Probability distribution function
    //
    virtual float pdf(const Ray& rayIn, const Ray& rayOut) const
    {
        return (1 / PI);
    }
    //---------------------------------------------------------------------
    // return emitted light of material
    //
    virtual glm::vec3 emitted() const { return glm::vec3(0.f); }

    //---------------------------------------------------------------------
    // T/F material is emissive
    //
    virtual bool emits() const { return false; }

protected:
    glm::vec3 m_diffuseColor;
};

#endif // !MATERIAL_H_

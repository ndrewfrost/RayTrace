/*
 * normal.h
 * Andrew Frost
 * 2020
 *
 

#ifndef NORMALMAT_H_
#define NORMALMAT_H_

#include "../core/material.h"

 ///////////////////////////////////////////////////////////////////////////
 // Normal                                                                //
 ///////////////////////////////////////////////////////////////////////////

class Normal : public Material
{
public:
    Normal() : Material() {};
    ~Normal() = default;

    virtual bool sample(const Ray& rayIn, Ray& rayOut,
                         const HitRecord& hitRecord) const
    {
        glm::vec3 dirOut = hitRecord.normal + rndPointUnitSphere();
        rayOut = Ray(hitRecord.point, dirOut);
        //attenuation = 0.5f * (hitRecord.normal + glm::vec3(1.0, 1.0, 1.0));
        return true;
    }
};

#endif // !NORMALMAT_H_
*/
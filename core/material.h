/*
 * material.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "ray.h"

///////////////////////////////////////////////////////////////////////////
// Material                                                              //
///////////////////////////////////////////////////////////////////////////

class Material
{
public:
    Material() : m_diffuseColor(0.f,0.f,0.f) {}

    Material(glm::vec3 color) : m_diffuseColor(color) {}

    virtual ~Material() = default;

    virtual bool scatter(const Ray& rayIn, Ray& rayOut,
        glm::vec3& attenuation, const HitRecord& hitRecord) const = 0;

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

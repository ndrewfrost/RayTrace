/*
 * BlinnPhong.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef BLINN_PHONG_H_
#define BLINN_PHONG_H_

#include "../core/material.h"

 ///////////////////////////////////////////////////////////////////////////
 // BlinnPhong                                                            //
 ///////////////////////////////////////////////////////////////////////////

class BlinnPhong : public Material
{
public:
    BlinnPhong(float ks, float kd, float kr, float specularExp, glm::vec3 color)
        : Material(color), m_ks(ks), m_kd(kd), m_kr(kr), m_specularExp(specularExp) {}

    ~BlinnPhong() = default;

    virtual bool scatter(const Ray& rayIn, Ray& rayOut,
        glm::vec3& attenuation, const HitRecord& hitRecord) const
    {
        glm::vec3 dirOut = hitRecord.normal + rndPointUnitSphere();
        rayOut = Ray(hitRecord.point, dirOut);
        attenuation = getAmbient() + getDiffuse() + getSpecular();
        return true;
    }

private:

    glm::vec3 getAmbient() const
    {
        return 0.08f * m_diffuseColor;
    }

    glm::vec3 getDiffuse() const
    {
        glm::vec3 diffuse = glm::vec3(0, 0, 0);

        return diffuse;
    }

    glm::vec3 getSpecular() const
    {
        glm::vec3 specular = glm::vec3(0, 0, 0);

        return specular;
    }

private:
    float m_ks, m_kd, m_kr;
    float m_specularExp;
};

#endif // !BLINN_PHONG_H_

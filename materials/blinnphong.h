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
/*
class BlinnPhong : public Material
{
public:
    BlinnPhong(float ks, float kd, float kr, float specularExp, glm::vec3 color)
        : m_color(color), m_ks(ks), m_kd(kd), m_kr(kr), m_specularExp(specularExp) {}

    ~BlinnPhong() = default;

    virtual bool sample(const Ray& rayIn, Ray& rayOut,
                        const HitRecord& hitRecord) const
    {
        glm::vec3 dirOut = hitRecord.normal + rndPointHemisphere();
        rayOut = Ray(hitRecord.point, dirOut);
        return true;
    }

    virtual glm::vec3 brdf(const Ray& rayIn, 
                           const Ray& rayOut,
                           const HitRecord& record) const
    {
        glm::vec3 half = glm::normalize(rayOut.direction() + rayIn.direction());
        
        // ambient
        glm::vec3 ambient = 0.08f * m_color;

        // diffuse
        glm::vec3 diffuse = glm::vec3(0.f);
        float diffuseAngle = glm::dot(rayOut.direction(), record.normal);
        if (diffuseAngle >= 0.f)
            diffuse = m_kd * diffuseAngle * m_color;

        // specular
        float specular = 0.f;
        float specAngle = glm::dot(half, record.normal);
        if (specAngle >= 0.f) 
            specular = m_ks * powf(specAngle, m_specularExp);

        return ambient + diffuse * specular;
        
    }

    virtual float pdf(const Ray& rayIn, const Ray& rayOut) const
    {
        return  1 / (2 * PI);
    }

    virtual glm::vec3 emitted() const { return glm::vec3(0); }

private:
    float m_ks, m_kd, m_kr;
    float m_specularExp;

    glm::vec3 m_color;
};
*/
#endif // !BLINN_PHONG_H_

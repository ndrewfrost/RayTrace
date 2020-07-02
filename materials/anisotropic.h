/*
 * anisotropic.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef ANISOTROPIC_H_
#define ANISOTROPIC_H_

#include "../core/material.h"

///////////////////////////////////////////////////////////////////////////
// Anisotropic                                                           //
///////////////////////////////////////////////////////////////////////////
/*
class Anisotropic : public Material
{
public:
    Anisotropic(float nv, float nu, glm::vec3 rs, glm::vec3 rd) 
        : m_nv(nv), m_nu(nu), m_rd(rd), m_rs(rs) {}

    virtual ~Anisotropic() = default;
    
    //---------------------------------------------------------------------
    //
    //
    virtual float pdf(const Ray& rayIn, const Ray& rayOut) const
    {
        glm::vec3 half = glm::normalize(rayIn.direction() + rayOut.direction());
        float cosTheta = absCosTheta(half);
        float denom = 1.f - sqr(cosTheta);
        
        if (denom <= 0.f) return 0.f;

        float exp = (m_nu * half.x * half.x + m_nv * half.y * half.y) / denom;

        float pdf_h = (sqrtf((m_nu + 1.f) * (m_nv + 1.f)) / (2.f * PI)) * powf(cosTheta, exp);
    
        return pdf_h / (4.0f * fabs(glm::dot(rayIn.direction(), rayOut.direction())));
    }
    
    
    //---------------------------------------------------------------------
    //
    //
    glm::vec3 f(const Ray & rayIn, const Ray& rayOut,
                const HitRecord& hitRecord) const
    {
        auto pow5 = [](float v) {return (v * v) * (v * v) * v; };

        //Diffuse
        glm::vec3 diffuse = ((28.f * m_rd) / (23.f * PI) * (glm::vec3(1.f) - m_rs))
                          * (1.f - pow5(1.f - .5f * fabs(glm::dot(hitRecord.normal, rayIn.direction())))) 
                          * (1.f - pow5(1.f - .5f * fabs(glm::dot(hitRecord.normal, rayOut.direction()))));
        diffuse = clamp(diffuse);

        //Specular
        glm::vec3 half = glm::normalize(rayIn.direction() + rayOut.direction());

        float halfDotNorm = fabs(glm::dot(hitRecord.normal, half));

        glm::vec3 sample(1.f, 1.f, .1f);

        float hDotW = fabs(glm::dot(half, rayOut.direction()));

        float normDotWI = fabs(glm::dot(hitRecord.normal, rayIn.direction()));

        float normDotWO = fabs(glm::dot(hitRecord.normal, rayOut.direction()));

        float left = sqrtf((m_nu + 1.f) * (m_nv + 1.f)) / (8.f * PI);

        float exp_f = (m_nu * sqr(half.x) + m_nv * sqr(half.y)) 
                    / (1.f - halfDotNorm * halfDotNorm);

        float rightNum = powf(halfDotNorm, exp_f);

        float rightDenom = hDotW * std::max(normDotWI, normDotWO);

        float right = rightNum / rightDenom;

        glm::vec3 schlick = m_rs + (glm::vec3(1.f) - m_rs) * pow5(1 - hDotW);

        glm::vec3 specular = clamp(left * right * schlick);

        return clamp(diffuse + specular);
    }

    //---------------------------------------------------------------------
    //
    //
    glm::vec3 samplef(const Ray& rayIn, const Ray& rayOut,
                      const HitRecord& hitRecord) const
    {
        float phi = std::atan(std::sqrtf((m_nu + 1) / (m_nv + 1))
                  * std::tan(PI * u[0] * 0.5f));


        if (u[0] >= 0.25f && u[0] < 0.5f) {
            phi = PI - PI;
        }
        else if (u[0] >= 0.5f && u[0] < 0.75f) {
            phi += PI;
        }
        else if (u[0] >= 0.75f && u[0] < 1.f) {
            phi = 2 * PI - phi;
        }

        float cosTheta = std::powf(u[1], 1 / ((m_nu * cos(phi) * cos(phi) 
                       + m_nv * sin(phi) * sin(phi) + 1)));

        float sinTheta = std::sqrtf(std::max(0.f, 1.f - cosTheta * cosTheta));

        glm::vec3 half = glm::vec3(sinTheta * cos(phi), sinTheta * sin(phi), cosTheta);
       
        if (!SameHemisphere(rayOut.direction(), half)) half = -half

        *wi = -rayOut.direction + 2.f * glm::dot(rayOut.direction(), half) * half;

        if (!SameHemisphere(rayOut.direction(), rayIn.direction())) return glm::vec3(0.f);

        return f(rayIn, RayOut, hitRecord);
    }
    
private:
    float     m_nu, m_nv;
    glm::vec3 m_rd, m_rs;

};
*/

#endif // !ANISOTROPIC_H_

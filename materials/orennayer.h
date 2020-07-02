/*
 * orennayer.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef OREN_NAYER_H_
#define OREN_NAYER_H_

#include "../core/material.h"

///////////////////////////////////////////////////////////////////////////
// OrenNayer                                                             //
///////////////////////////////////////////////////////////////////////////
 
class OrenNayer : public Material
{
public:
    OrenNayer(glm::vec3 color, float sigmaDeg) : m_color(color) 
    {
        float sigma = degree2Rad(sigmaDeg);
        float sigma2 = sqr(sigma);
        m_a = 1.f - (sigma2 / (2.f * (sigma2 + 0.33f)));
        m_b = 0.45f * sigma2 / (sigma2 + 0.09f);
    };

    virtual glm::vec3 f(const Ray& rayIn, Ray& rayOut,
        const HitRecord& hitRecord) const
    {
        float sinThetaIn  = sinTheta(rayIn.direction());
        float sinThetaOut = sinTheta(rayOut.direction());
       
        float maxCos = 0.f;
        if (sinThetaIn > 0.0001f && sinThetaOut > 0.0001f) {
            float sinPhiIn  = sinPhi(rayIn.direction());
            float cosPhiIn  = cosPhi(rayIn.direction());
            float sinPhiOut = sinPhi(rayOut.direction());
            float cosPhiOut = cosPhi(rayOut.direction());
            float dcos = cosPhiIn * cosPhiOut + sinPhiIn * sinPhiOut;
            maxCos = std::max(0.f, dcos);
        }

        float sinAlpha, tanBeta;
        if (absCosTheta(rayIn.direction()) > absCosTheta(rayOut.direction())) {
            sinAlpha = sinThetaOut;
            tanBeta  = sinThetaIn / absCosTheta(rayIn.direction());
        }
        else {
            sinAlpha = sinThetaIn;
            tanBeta  = sinThetaOut / absCosTheta(rayOut.direction());
        }
        return m_color * (m_a + m_b * maxCos * sinAlpha * tanBeta) / PI;
    }
    
private:
    glm::vec3 m_color;
    float     m_a, m_b;
};

#endif // !OREN_NAYER_H_

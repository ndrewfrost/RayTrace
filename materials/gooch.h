/*
 * gooch.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef GOOCH_H_
#define GOOCH_H_

#include "../core/material.h"

///////////////////////////////////////////////////////////////////////////
// Gooch                                                                 //
///////////////////////////////////////////////////////////////////////////

class Gooch : public Material
{
public:
    Gooch(glm::vec3 color, glm::vec3 highlight = glm::vec3(1.f)) 
        : m_diffuseColor(color), m_highlight(highlight) {}

    ~Gooch() = default;

    virtual glm::vec3 f(const Ray& rayIn, Ray& rayOut,
                        const HitRecord& hitRecord) const
    {
        glm::vec3 cool = glm::vec3(0.0f, 0.0f, 0.55f) + 0.25f * m_diffuseColor;
        glm::vec3 warm = glm::vec3(0.3f, 0.3f, 0.0f) + 0.25f * m_diffuseColor;

        glm::vec3 r = 2.f * glm::dot(hitRecord.normal, rayOut.direction()) * hitRecord.normal - rayOut.direction();
        float s = clamp(100.f * glm::dot(r, -rayIn.direction()) - 97.f);
        float t = (glm::dot(hitRecord.normal, rayOut.direction()) + 1.f) / 2.f;

        return (s * m_highlight) + (1.f - s) * (t * warm + (1.f - t) * cool);
    }

private:
    glm::vec3 m_diffuseColor;
    glm::vec3 m_highlight;

};

#endif // !GOOCH_H_

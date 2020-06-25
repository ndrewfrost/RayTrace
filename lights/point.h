/*
 * point.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "../core/light.h"

///////////////////////////////////////////////////////////////////////////
// Point Light                                                           //
///////////////////////////////////////////////////////////////////////////

class PointLight : public Light
{
public:
    PointLight(glm::vec3 pos, glm::vec3 color, float intensity)
        : m_position(pos), m_color(color), m_intensity(intensity) {}

    ~PointLight() = default;

    virtual glm::vec3 sampleLight(glm::vec3 dest) {
        return  glm::length(m_position-dest) * m_intensity * m_color;
    }

private:
    glm::vec3 m_position;
    glm::vec3 m_color;
    float     m_intensity;
};

#endif // !POINTLIGHT_H_

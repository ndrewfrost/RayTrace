/*
 * distant.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef DISTANTLIGHT_H_
#define DISTANTLIGHT_H_

#include "../core/light.h"

///////////////////////////////////////////////////////////////////////////
// Distant Light                                                         //
///////////////////////////////////////////////////////////////////////////

class DistantLight : public Light
{
public:
    DistantLight(glm::vec3 dir, glm::vec3 color, float intensity)
        : m_direction(dir), m_color(color), m_intensity(intensity) {}

    ~DistantLight() = default;

    virtual glm::vec3 sampleLight(glm::vec3 dest) {
        return glm::vec3(0);
    }

private:
    glm::vec3 m_direction;
    glm::vec3 m_color;
    float     m_intensity;
};

#endif // !POINTLIGHT_H_

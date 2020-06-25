/*
 * spotlight.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

#include "../core/light.h"

///////////////////////////////////////////////////////////////////////////
// Spot Light                                                            //
///////////////////////////////////////////////////////////////////////////

class SpotLight : public Light {
public:
    SpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 color, float intensity, float r) 
        : m_position(pos), m_direction(dir), m_color(color), m_intensity(intensity), m_radius(r) {}

    ~SpotLight() = default;

    virtual glm::vec3 sampleLight(glm::vec3 dest) {
        return glm::vec3(0);
    }

private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_color;
    float     m_intensity;
    float     m_radius;
};

#endif // !SPOTLIGHT_H_

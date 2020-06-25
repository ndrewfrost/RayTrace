/*
 * area.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "../core/light.h"
#include "../core/geometry.h"

///////////////////////////////////////////////////////////////////////////
// Area Light                                                            //
///////////////////////////////////////////////////////////////////////////

class AreaLight : public Light {
public:
    AreaLight(std::shared_ptr<Geometry> shape, glm::vec3 color, float intensity)
        : m_shape(shape), m_color(color), m_intensity(intensity) {}

    ~AreaLight() = default;

    std::shared_ptr<Geometry> getShape() const { return m_shape; }

    virtual glm::vec3 sampleLight(glm::vec3 dest) {
        return glm::vec3(0);
    }

private:
    std::shared_ptr<Geometry> m_shape;
    glm::vec3                 m_color;
    float                     m_intensity;
};

#endif // !AREALIGHT_H_

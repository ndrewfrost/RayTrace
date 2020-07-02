/*
 * emissive.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef EMISSIVE_H_
#define EMISSIVE_H_

#include "../core/material.h"

///////////////////////////////////////////////////////////////////////////
// Emissive                                                              //
///////////////////////////////////////////////////////////////////////////

class Emissive : public Material
{
public:
    Emissive(glm::vec3 color, float intensity)
        : m_color(color), m_intensity(intensity) {}

    virtual glm::vec3 f(const Ray& rayIn, Ray& rayOut,
        const HitRecord& hitRecord) const { return glm::vec3(0.f); }

    virtual glm::vec3 sample(const Ray& rayIn, Ray& rayOut,
        const HitRecord& hitRecord) { return glm::vec3(0.f);  }

    virtual float pdf(const Ray& rayIn, const Ray& rayOut) { return 0; }

    virtual glm::vec3 emitted() const { return m_color * m_intensity; }

    virtual bool emits() const { return true; }

private:
    glm::vec3 m_color;
    float     m_intensity;
};

/*
class Emissive : public Material
{
public:
    Emissive(glm::vec3 color, float intensity)
        : m_color(color), intensity(intensity) {}

    ~Emissive() = default;

    virtual bool sample(const Ray& rayIn, Ray& rayOut,
                        const HitRecord& hitRecord) const 
    {
        return false;
    }

    virtual glm::vec3 emitted() const {
        return intensity * m_color;
    }

    virtual float pdf(const Ray& rayIn, const Ray& rayOut) const
    {
        return 1;
    }

    virtual glm::vec3 brdf(const Ray& rayIn,
        const Ray& rayOut,
        const HitRecord& record) const
    {
        return glm::vec3(0, 0, 0);
    }

private:
    glm::vec3 m_color;
    float     intensity;
};
*/
#endif // !EMISSIVE_H_
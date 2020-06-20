/*
 * sphere.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "../core/geometry.h"

 ///////////////////////////////////////////////////////////////////////////
 // Sphere                                                                //
 ///////////////////////////////////////////////////////////////////////////

class Sphere : public Geometry
{
public:
    Sphere(glm::vec3 center, float radius) : m_center(center), m_radius(radius) {}

    ~Sphere() {}

    float intersect(const Ray& ray);

private:
    glm::vec3 m_center;
    float     m_radius;
};


#endif // !SPHERE_H_

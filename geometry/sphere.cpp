/*
 * sphere.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "sphere.h"

 ///////////////////////////////////////////////////////////////////////////
 // Sphere                                                                //
 ///////////////////////////////////////////////////////////////////////////

 //-------------------------------------------------------------------------
 // Given a ray, returns true if ray intersects sphere
 // else returns false
 //
bool Sphere::intersect(const Ray& ray)
{
    glm::vec3 oc = ray.origin() - m_center;

    float a = glm::dot(ray.direction(), ray.direction());
    float half_b = /* (2 *) */ glm::dot(oc, ray.direction());
    float c = glm::dot(oc, oc) - m_radius * m_radius;

    float discriminant = half_b * half_b - a * c;

    // Hit
    if (discriminant > 0) {
        return true;
        //return (-half_b - sqrt(discriminant)) / a;
    }

    // Miss
    return false;
}

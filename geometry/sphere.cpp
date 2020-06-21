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
bool Sphere::intersect(const Ray& ray, float tMin, float tMax, HitRecord& record)
{
    glm::vec3 oc = ray.origin() - m_center;
    float a = glm::dot(ray.direction(), ray.direction());
    float halfB = /* (2 */  glm::dot(oc, ray.direction());
    float c = glm::dot(oc, oc) - sqr(m_radius);

    float discriminant = sqr(halfB) - a * c;
    float root = std::sqrtf(discriminant);

    // Hit
    if (discriminant > 0) {

        float t = (-halfB - root) / a;
        if (t < tMax && t > tMin) {
            record.t = t;
            record.point = ray.at(record.t);
            glm::vec3 outNormal = (record.point - m_center) / m_radius;
            record.setFaceNormal(ray, outNormal);
            record.material = m_material;
            return true;
        }

        t = (-halfB + root) / a;
        if (t < tMax && t > tMin) {
            record.t = t;
            record.point = ray.at(record.t);
            glm::vec3 outNormal = (record.point - m_center) / m_radius;
            record.setFaceNormal(ray, outNormal);
            record.material = m_material;
            return true;
        }
    }

    // Miss
    return false;

}

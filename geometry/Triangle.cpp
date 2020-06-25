/*
 * triangle.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "triangle.h"

///////////////////////////////////////////////////////////////////////////
// Triangle                                                              //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
// Möller–Trumbore intersection algorithm
//
bool Triangle::intersect(const Ray& ray, float tMin, float tMax, HitRecord& record)
{
    glm::vec3 v0v1 = m_v1 - m_v0;
    glm::vec3 v0v2 = m_v2 - m_v0;

    glm::vec3 p = glm::cross(ray.direction(), v0v2);

    float determinant = glm::dot(v0v1, p);

    // Back face culling
    if (determinant < 0.00001f) return false;

    float invDeterminant = 1.0f / determinant;

    glm::vec3 s = ray.origin() - m_v0;
    float u = invDeterminant * glm::dot(s, p);
    if (u < 0 || u > 1) return false;

    glm::vec3 q = glm::cross(s, v0v1);
    float v = glm::dot(ray.direction(), q) * invDeterminant;
    if (v < 0 || u + v > 1) return false;

    float t = glm::dot(v0v2, q) * invDeterminant;

    // Hit
    if (t < tMax && t > tMin) {
        record.frontFace = true;
        record.material = m_material;
        record.t = t;
        record.point = ray.at(t);
        record.normal = m_faceNormal;
        return true;
    }
    // Miss
    return false;
}
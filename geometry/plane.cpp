/*
 * plane.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "plane.h"

///////////////////////////////////////////////////////////////////////////
// Plane                                                                 //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
// Constructor
//
Plane::Plane(glm::vec3 center, float width, float height,
             glm::vec3 rotation, shared_ptr<Material> material)
    : m_center(center), m_width(width), m_height(height), m_material(material)
{   
    // BL
    m_v0 = glm::vec3(-width / 2.0f, 0.0f, -height / 2.0f);
    m_v0 = rotate(m_v0, rotation);
    m_v0 = center + m_v0;
    
    // BR
    m_v1 = glm::vec3(width / 2.0f, 0.0f, -height / 2.0f);
    m_v1 = rotate(m_v1, rotation);
    m_v1 = center + m_v1;
    
    // TR
    m_v2 = glm::vec3(width / 2.0f, 0.0f, height / 2.0f);
    m_v2 = rotate(m_v2, rotation);
    m_v2 = center + m_v2;

    // TL
    m_v3 = glm::vec3(-width / 2.0f, 0.0f, height / 2.0f);
    m_v3 = rotate(m_v3, rotation);
    m_v3 = center + m_v3;

    m_normal = glm::vec3(0, 1, 0);
    m_normal = rotate(m_normal, rotation);
}

//-------------------------------------------------------------------------
// Ray / Quad interseption
//
bool Plane::intersect(const Ray& ray, float tMin, float tMax, HitRecord& record)
{
    float denom = glm::dot(m_normal, ray.direction());

    if (fabs(denom) > 0.0001f) {

        float t = glm::dot(m_center - ray.origin(), m_normal) / denom;

        if (t < 0) return false;

        float projection1 = glm::dot((m_v0 - ray.at(t)), (m_v0 - m_v1)) / m_width;
        if (projection1 >= m_width || projection1 < 0) return false;

        float projection2 = glm::dot((m_v0 - ray.at(t)), (m_v0 - m_v3)) / m_height;
        if (projection2 >= m_height || projection2 < 0) return false;

        // Hit
        if (t < tMax && t > tMin) {
            record.frontFace = (denom > 0) ? false : true;
            record.material = m_material;
            record.t = t;
            record.point = ray.at(t);
            record.normal = glm::normalize(m_normal);
            return true;
        }
    }

    return false;
}
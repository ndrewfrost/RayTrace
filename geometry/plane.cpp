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

    m_normal = glm::vec3(0.f, 1.f, 0.f);
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

//-------------------------------------------------------------------------
// gen Bounding box
//
bool Plane::boundingBox(aabb& bBox)
{
    float xmin = m_v0.x < m_v1.x ? (m_v0.x < m_v2.x ? (m_v0.x < m_v3.x ? m_v0.x : m_v3.x) : m_v2.x)
        : (m_v1.x < m_v2.x ? (m_v1.x < m_v3.x ? m_v1.x : m_v3.x) : m_v2.x);
    float ymin = m_v0.y < m_v1.y ? (m_v0.y < m_v2.y ? (m_v0.y < m_v3.y ? m_v0.y : m_v3.y) : m_v2.y)
        : (m_v1.y < m_v2.y ? (m_v1.y < m_v3.y ? m_v1.y : m_v3.y) : m_v2.y);
    float zmin = m_v0.z < m_v1.z ? (m_v0.z < m_v2.z ? (m_v0.z < m_v3.z ? m_v0.z : m_v3.z) : m_v2.z)
        : (m_v1.z < m_v2.z ? (m_v1.z < m_v3.z ? m_v1.z : m_v3.z) : m_v2.z);

    float xmax = m_v0.x > m_v1.x ? (m_v0.x > m_v2.x ? (m_v0.x > m_v3.x ? m_v0.x : m_v3.x) : m_v2.x)
        : (m_v1.x > m_v2.x ? (m_v1.x > m_v3.x ? m_v1.x : m_v3.x) : m_v2.x);
    float ymax = m_v0.y > m_v1.y ? (m_v0.y > m_v2.y ? (m_v0.y > m_v3.y ? m_v0.y : m_v3.y) : m_v2.y)
        : (m_v1.y > m_v2.y ? (m_v1.y > m_v3.y ? m_v1.y : m_v3.y) : m_v2.y);
    float zmax = m_v0.z > m_v1.z ? (m_v0.z > m_v2.z ? (m_v0.z > m_v3.z ? m_v0.z : m_v3.z) : m_v2.z)
        : (m_v1.z > m_v2.z ? (m_v1.z > m_v3.z ? m_v1.z : m_v3.z) : m_v2.z);

    // if min == max for any axis add a tiny amount to create a 3D volume since planes have no volume 
    if (xmin == xmax) xmin -= 0.0001f; xmax += 0.0001f;
    if (ymin == ymax) ymin -= 0.0001f; ymax += 0.0001f;
    if (zmin == zmax) zmin -= 0.0001f; zmax += 0.0001f;

    bBox = aabb(glm::vec3(xmin, ymin, zmin),
        glm::vec3(xmax, ymax, zmax));
    return true;
}

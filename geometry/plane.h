/*
 * plane.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "../core/geometry.h"

 ///////////////////////////////////////////////////////////////////////////
 // Plane                                                                 //
 ///////////////////////////////////////////////////////////////////////////

class Plane : public Geometry
{
public:
    Plane(glm::vec3 center, float width, float height,
        glm::vec3 rotation, std::shared_ptr<Material> material);

    virtual ~Plane() = default;

    virtual bool intersect(const Ray& ray, float tMin, float tMax, HitRecord& record);
    
private:
    glm::vec3 m_v0, m_v1, m_v2, m_v3;
    glm::vec3 m_normal;

    glm::vec3 m_center;
    float     m_width;
    float     m_height;

    shared_ptr<Material> m_material;
};
#endif // !PLANE_H_

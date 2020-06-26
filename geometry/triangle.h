/*
 * triangle.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../core/geometry.h"

///////////////////////////////////////////////////////////////////////////
// Triangle                                                              //
///////////////////////////////////////////////////////////////////////////

class Triangle : public Geometry
{
public:
    Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, std::shared_ptr<Material> material)
    : m_v0(v0), m_v1(v1), m_v2(v2), m_material(material) {
        glm::vec3 v = m_v1 - m_v0;
        glm::vec3 w = m_v2 - m_v0;
        m_faceNormal = glm::vec3((v.y * w.z - v.z * w.y), 
                                 (v.z * w.x - v.x * w.z),
                                 (v.x * w.y - v.y * w.x));
    }

    virtual ~Triangle() = default;

    virtual bool intersect(const Ray& ray, float tMin, float tMax, HitRecord& record);

    virtual bool boundingBox(aabb& bBox);

private:
    glm::vec3 m_v0, m_v1, m_v2;
    glm::vec3 m_n0, m_n1, m_n2; // TODO
    glm::vec3 m_faceNormal;

    shared_ptr<Material> m_material;
};

#endif // !TRIANGLE_H_

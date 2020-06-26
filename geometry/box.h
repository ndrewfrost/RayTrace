/*
 * box.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef BOX_H_
#define BOX_H_

#include <vector>
#include <memory>

#include "plane.h"

///////////////////////////////////////////////////////////////////////////
// Box                                                                   //
///////////////////////////////////////////////////////////////////////////

class Box : public Geometry
{
public:
    Box(glm::vec3 center, float width, float height, float depth,
        glm::vec3 rotation, std::shared_ptr<Material> material);

    virtual ~Box() = default;

    virtual bool intersect(const Ray& ray, float tMin, float tMax, HitRecord& record);


private:
    std::vector<std::shared_ptr<Geometry>> m_planes;
};
#endif // !PLANE_H_

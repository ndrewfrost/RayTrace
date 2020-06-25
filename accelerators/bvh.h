/*
 * bvh.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef BVH_H_
#define BVH_H_

#include <algorithm>
#include <iostream>

#include "../core/geometry.h"
#include "../core/scene.h"

///////////////////////////////////////////////////////////////////////////
// Bounding Volume Hierarchy Node                                        //
///////////////////////////////////////////////////////////////////////////

class BVHNode : public Geometry
{
public:
    BVHNode() = default;

    BVHNode(std::vector<shared_ptr<Geometry>> & objects, size_t start, size_t end);

    BVHNode(Scene& scene)
        : BVHNode(scene.getObjects(), 0, scene.getObjects().size()) {}

    virtual ~BVHNode() = default;

    virtual bool intersect(const Ray& ray, float tMin, float tMax, HitRecord& record);

    virtual bool boundingBox(aabb& bBox);

private:
    shared_ptr<Geometry> m_left;
    shared_ptr<Geometry> m_right;
    aabb                 m_box;
};

#endif // !BVH_H_

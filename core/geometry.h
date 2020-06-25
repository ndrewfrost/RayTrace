/*
 * geometry.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <memory>

#include "../common/math.h"
#include "material.h"
#include "ray.h"

///////////////////////////////////////////////////////////////////////////
// Geometry                                                              //
///////////////////////////////////////////////////////////////////////////

class Geometry
{
public:
    Geometry() = default;

    virtual ~Geometry() = default;

    virtual bool intersect(const Ray & ray, float tMin, float tMax, HitRecord& record) = 0;

    virtual bool boundingBox(aabb& bBox) = 0;
};


#endif // !SHAPE_H_

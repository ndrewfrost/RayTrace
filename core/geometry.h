/*
 * geometry.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "../common/glm_common.h"
#include "ray.h"

 ///////////////////////////////////////////////////////////////////////////
 // Geometry                                                              //
 ///////////////////////////////////////////////////////////////////////////

class Geometry
{
public:
    Geometry() = default;

    virtual ~Geometry() = default;

    virtual float intersect(const Ray& ray) = 0;
};


#endif // !SHAPE_H_
/*
 * geometry.h
 * Andrew Frost
 * 2020
 *
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
// HitRecord                                                             //
///////////////////////////////////////////////////////////////////////////

struct HitRecord
{
    glm::vec3 point;
    glm::vec3 normal;
    float     t;
    bool      frontFace;

    inline void setFaceNormal(const Ray & ray, const glm::vec3 & outNormal)
    {
        frontFace = glm::dot(ray.direction(), outNormal) < 0;
        normal = frontFace ? outNormal : -outNormal;
    }
};

///////////////////////////////////////////////////////////////////////////
// Geometry                                                              //
///////////////////////////////////////////////////////////////////////////

class Geometry
{
public:
    Geometry() = default;

    virtual ~Geometry() = default;

    virtual bool intersect(const Ray & ray, float tMin, float tMax, HitRecord& record) = 0;
};


#endif // !SHAPE_H_

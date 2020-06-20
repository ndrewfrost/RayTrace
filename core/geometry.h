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

using std::shared_ptr;

///////////////////////////////////////////////////////////////////////////
// HitRecord                                                             //
///////////////////////////////////////////////////////////////////////////

struct HitRecord
{
    float t;
    bool frontFace;
    glm::vec3 point;
    glm::vec3 normal;        
    shared_ptr<Material> material;

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

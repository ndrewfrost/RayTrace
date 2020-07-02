/*
 * ray.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef RAY_H_
#define RAY_H_

#include "../common/math.h"
#include <memory>

using std::shared_ptr;
class Material;

///////////////////////////////////////////////////////////////////////////
// Ray                                                                   //
///////////////////////////////////////////////////////////////////////////

class Ray
{
public:
    Ray() = default;

    ~Ray() = default;

    Ray(const glm::vec3& origin, const glm::vec3& direction)
        : m_origin(origin), m_direction(glm::normalize(direction)) {}

    glm::vec3 origin()    const { return m_origin; }
    glm::vec3 direction() const { return m_direction; }

    glm::vec3 at(float t) const { return m_origin + t * m_direction; }

public:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
};

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

    inline void setFaceNormal(const Ray& ray, const glm::vec3& outNormal)
    {
        frontFace = glm::dot(ray.direction(), outNormal) < 0;
        normal = frontFace ? outNormal : -outNormal;
    }
};


#endif // !RAY_H_


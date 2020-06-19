/*
 * ray.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef RAY_H_
#define RAY_H_

#include "../common/glm_common.h"

 ///////////////////////////////////////////////////////////////////////////
 // Ray                                                                   //
 ///////////////////////////////////////////////////////////////////////////

class Ray
{
public:
    Ray() = default;

    ~Ray() = default;

    Ray(const glm::vec3& origin, const glm::vec3& direction)
        : m_origin(origin), m_direction(direction) {}

    glm::vec3 origin()    const { return m_origin; }
    glm::vec3 direction() const { return m_direction; }

public:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
};

#endif // !RAY_H_


/*
 * aabb.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef AABB_H_
#define AABB_H_

#include "../common/math.h"
#include "../core/ray.h"

///////////////////////////////////////////////////////////////////////////
// AABB                                                                  //
///////////////////////////////////////////////////////////////////////////

class aabb
{
public:
    aabb() = default;

    aabb(glm::vec3 min, glm::vec3 max) : m_vMin(min), m_vMax(max) {}

    virtual ~aabb() = default;

    bool intersect(const Ray& ray, float tMin, float tMax)
    {
        for (int i = 0; i < 3; i++) {
            float invDir = 1.0f / ray.direction()[i];
            float t0 = (m_vMin[i] - ray.origin()[i]) * invDir;
            float t1 = (m_vMax[i] - ray.origin()[i]) * invDir;
            
            if (invDir < 0.0f)
                std::swap(t0, t1);

            tMin = t0 > tMin ? t0 : tMin;
            tMax = t1 < tMax ? t1 : tMax;

            if (tMax <= tMin)
                return false;
        }
        return true;
    }

    static aabb surroundingBox(aabb & box0, aabb & box1)
    {
        glm::vec3 min = glm::vec3(fmin(box0.min().x, box1.min().x), 
                                  fmin(box0.min().y, box1.min().y), 
                                  fmin(box0.min().z, box1.min().z));
        glm::vec3 max = glm::vec3(fmax(box0.max().x, box1.max().x), 
                                  fmax(box0.max().y, box1.max().y),
                                  fmax(box0.max().z, box1.max().z));

        return aabb(min, max);
    }

    glm::vec3 min() const { return m_vMin;  }
    glm::vec3 max() const { return m_vMax; }

private:
    glm::vec3 m_vMin;
    glm::vec3 m_vMax;
};

#endif // !AABB_H_

/*
 * scene.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>

#include "geometry.h"
#include "light.h"
#include "../lights/area.h"

///////////////////////////////////////////////////////////////////////////
// Scene                                                                 //
///////////////////////////////////////////////////////////////////////////

class Scene
{
public:
    Scene() = default;
    
    Scene(std::vector<std::shared_ptr<Geometry>> geometry, 
          std::vector<std::shared_ptr<Light>>    lights)
        : m_objects(geometry), m_lights(lights) {}
    
    ~Scene() = default;

    bool intersectGeometry(const Ray& ray, float tMin, float tMax, HitRecord& record);

    bool boundingBox(aabb& bBox);
    
    glm::vec3 sampleLights(const Ray & ray, HitRecord & record);
       
    std::vector<std::shared_ptr<Geometry>>& getObjects() { return m_objects; }

private:
    std::vector<std::shared_ptr<Light>>    m_lights;
    std::vector<std::shared_ptr<Geometry>> m_objects;

};

#endif // !SCENE_H_

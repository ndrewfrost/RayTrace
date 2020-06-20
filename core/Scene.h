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
#include "../geometry/sphere.h"

 ///////////////////////////////////////////////////////////////////////////
 // Scene                                                                 //
 ///////////////////////////////////////////////////////////////////////////

class Scene
{
public:
    Scene() = default;

    Scene(std::vector<std::shared_ptr<Geometry>> geometry) : m_objects(geometry) {}

    ~Scene() = default;

    std::vector<std::shared_ptr<Geometry>> m_objects;

};

#endif // !SCENE_H_

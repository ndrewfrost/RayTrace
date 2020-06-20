/*
 * scene.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "scene.h"

///////////////////////////////////////////////////////////////////////////
// Scene                                                                 //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
//
//
bool Scene::intersect(const Ray& ray, float tMin, float tMax, HitRecord& record)
{
    HitRecord tempRecord;
    bool intersect = false;
    float closest = tMax;

    for (const auto & object : m_objects) {
        if (object->intersect(ray, tMin, closest, tempRecord)) {
            intersect = true;
            closest = tempRecord.t;
            record = tempRecord;
        }
    }

    return intersect;
}

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
 // check ray intersection with all objects / area lights in the scene
 //
bool Scene::intersectGeometry(const Ray& ray, float tMin, float tMax, HitRecord& record)
{
    HitRecord tempRecord;
    bool intersect = false;
    float closest = tMax;

    // Physical Objects
    for (const auto& object : m_objects) {
        if (object->intersect(ray, tMin, closest, tempRecord)) {
            intersect = true;
            closest = tempRecord.t;
            record = tempRecord;
        }
    }

    return intersect;
}

//-------------------------------------------------------------------------
// Generate a scene Bounding Box
//
bool Scene::boundingBox(aabb& bBox)
{
    if (m_objects.empty()) return false;

    aabb tempBox;
    bool firstBox = true;

    // Physical Objects
    for (const auto& object : m_objects) {
        if (!object->boundingBox(tempBox)) return false;
        bBox = firstBox ? tempBox : aabb::surroundingBox(bBox, tempBox);
        firstBox = false;
    }

    return false;
}

//-------------------------------------------------------------------------
// sample light sources
//
glm::vec3 Scene::sampleLights(const Ray& ray, HitRecord& record)
{
    /*
        ray.direction in
        ray.origin

        distance t from origin
        point of contact
        normal at contact
        face or backface
        material
    */

    glm::vec3 color = glm::vec3(0.f, 0.f, 0.f);

    for (auto& light : m_lights) {
        color += light->sampleLight(record.point);
    }

    return color;
}
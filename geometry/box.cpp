/*
 * box.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "box.h"

///////////////////////////////////////////////////////////////////////////
// Box                                                                   //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
// Generate 6 planes for the box faces
//
Box::Box(glm::vec3 center, float width, float height, float depth, 
         glm::vec3 rotation, std::shared_ptr<Material> material)
{    
    // Top
    glm::vec3 planeCenter = rotate(glm::vec3(0.f, height / 2.f, 0.f), rotation);
    m_planes.push_back(std::make_unique<Plane>(Plane(center + planeCenter, width, depth, rotation, material)));
    
    // Bottom
    planeCenter = rotate(glm::vec3(0.f, height / 2.f, 0.f), rotation);
    m_planes.push_back(std::make_unique<Plane>(Plane(center - planeCenter, width, depth, rotation + glm::vec3(-180.f, 0.f, 0.f), material)));
    
    // Front
    planeCenter = rotate(glm::vec3(0.f, 0.f, depth / 2.f), rotation);
    m_planes.push_back(std::make_unique<Plane>(Plane(center + planeCenter, width, height, rotation + glm::vec3(90.f, 0.f, 0.f), material)));
    
    // Back
    planeCenter = rotate(glm::vec3(0.f, 0.f, depth / 2.f), rotation);
    m_planes.push_back(std::make_unique<Plane>(Plane(center - planeCenter, width, height, rotation + glm::vec3(-90.f, 0.f, 0.f), material)));

    // Right
    planeCenter = rotate(glm::vec3(width / 2.f, 0.f, 0.f), rotation);  
    glm::vec3 planeRotation = glm::vec3(-rotation.y, rotation.x, rotation.z - 90.f);
    m_planes.push_back(std::make_unique<Plane>(Plane(center + planeCenter, height, depth, planeRotation, material)));

    // Left
    planeCenter = rotate(glm::vec3(width / 2.0f, 0.f, 0.f), rotation);
    planeRotation = planeRotation + glm::vec3(180.f,0.f,0.f);
    m_planes.push_back(std::make_unique<Plane>(Plane(center - planeCenter, height, depth, planeRotation, material)));
    
}

//-------------------------------------------------------------------------
// Check through List of planes for closest intersection
//
bool Box::intersect(const Ray& ray, float tMin, float tMax, HitRecord& record)
{
    HitRecord tempRecord;
    bool intersect = false;
    float closest = tMax;

    for (auto & plane : m_planes) {
        if (plane->intersect(ray, tMin, closest, tempRecord)) {
            intersect = true;
            closest = tempRecord.t;
            record = tempRecord;
        }
    }
    return intersect;
}

//-------------------------------------------------------------------------
// Generate bounding box for box
//
bool Box::boundingBox(aabb& bBox)
{
    aabb one, two;
    m_planes.at(0)->boundingBox(one);
    for (std::size_t ind = 1; ind != m_planes.size(); ++ind) {
        m_planes.at(ind)->boundingBox(two);
        one = aabb::surroundingBox(one, two);
    }

    bBox = one;
    return true;
}

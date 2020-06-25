/*
 * bvh.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "bvh.h"

///////////////////////////////////////////////////////////////////////////
// Box Comparitors                                                       //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
//
//
inline bool box_compare(const shared_ptr<Geometry> a, 
                        const shared_ptr<Geometry> b, 
                        int axis) {
    aabb aBox;
    aabb bBox;

    if (!a->boundingBox(aBox) || !b->boundingBox(bBox))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return aBox.min()[axis] < bBox.min()[axis];
}

//-------------------------------------------------------------------------
//
//
bool xBoxCompare(const shared_ptr<Geometry> a, 
                 const shared_ptr<Geometry> b) 
{
    return box_compare(a, b, 0);
}

//-------------------------------------------------------------------------
//
//
bool yBoxCompare(const shared_ptr<Geometry> a, 
                 const shared_ptr<Geometry> b) 
{
    return box_compare(a, b, 1);
}

//-------------------------------------------------------------------------
//
//
bool zBoxCompare(const shared_ptr<Geometry> a, 
                 const shared_ptr<Geometry> b) 
{
    return box_compare(a, b, 2);
}

///////////////////////////////////////////////////////////////////////////
// BVH Node                                                              //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
// Recursively generate a BVH split randomly along axis
//
BVHNode::BVHNode(std::vector<shared_ptr<Geometry>> & objects, size_t start, size_t end)
{
    // Random Axis comparison for BVH
    int axis = randomInt(0, 2);
    auto comparator = (axis == 0) ? xBoxCompare
                    : (axis == 1) ? yBoxCompare
                                  : zBoxCompare;

    size_t span = end - start;

    // One object left cant split
    if (span == 1) {
        m_left = m_right = objects[start];
    }
    // Two objects left, split into L R nodes
    else if (span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            m_left  = objects[start];
            m_right = objects[start + 1];
        }
        else {
            m_left = objects[start + 1];
            m_right = objects[start];
        }
    }
    // > 2 objects left
    else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        size_t mid = start + span / 2;
        m_left  = std::make_shared<BVHNode>(objects, start, mid);
        m_right = std::make_shared<BVHNode>(objects, mid, end);
    }

    aabb boxLeft, boxRight;

    if (!m_left->boundingBox(boxLeft) || !m_right->boundingBox(boxRight))
        std::cerr << "No bounding box in bvhNode constructor." << std::endl;

    m_box = aabb::surroundingBox(boxLeft, boxRight);
}

//-------------------------------------------------------------------------
//
//
bool BVHNode::intersect(const Ray& ray, float tMin, float tMax, HitRecord& record)
{
    if (!m_box.intersect(ray, tMin, tMax)) return false;

    bool intersectLeft = m_left->intersect(ray, tMin, tMax, record);
    bool intersectRight = m_right->intersect(ray, tMin, tMax, record);

    return intersectLeft || intersectRight;
}

//-------------------------------------------------------------------------
//
//
bool BVHNode::boundingBox(aabb& bBox)
{
    bBox = m_box;
    return true;
}

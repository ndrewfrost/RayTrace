/*
 * pinhole.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "pinhole.h"

 ///////////////////////////////////////////////////////////////////////////
 // Pinhole                                                               //
 ///////////////////////////////////////////////////////////////////////////

 //-------------------------------------------------------------------------
 //
 //
Pinhole::Pinhole(glm::vec3 origin, glm::vec3 lookAt, glm::vec3 vup, float hfov, float aspectRatio)
    : Camera(origin, lookAt, vup, hfov, aspectRatio)
{
}

//-------------------------------------------------------------------------
//
//
Ray Pinhole::getRay(float s, float t) const
{
    return Ray(m_origin, m_lowerLeftCorner + (s * m_horizontal) + (t * m_vertical) - m_origin);
}

//-------------------------------------------------------------------------
//
//
void Pinhole::printCamera()
{
    std::cout << "Pinhole Camera" << std::endl;
    std::cout << "origin     : " << vecToString(m_origin) << std::endl;
}



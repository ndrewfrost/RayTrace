/*
 * thinlens.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "thinlens.h"

///////////////////////////////////////////////////////////////////////////
// Thin Lens                                                             //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
//
//
ThinLens::ThinLens(glm::vec3 origin, glm::vec3 lookAt, glm::vec3 vup, 
    float hfov, float aspectRatio, float aperture, float focalDistance)
{
    float theta          = degree2Rad(hfov);
    float width          = tan(theta / 2.f);
    float viewportWidth  = 2.f * width;
    float viewportHeight = aspectRatio * viewportWidth;

    m_w = glm::normalize(origin - lookAt);
    m_u = glm::normalize(glm::cross(vup, m_w));
    m_v = glm::cross(m_w, m_u);

    m_origin          = origin;
    m_horizontal      = focalDistance * viewportWidth * m_u;
    m_vertical        = focalDistance * viewportHeight * m_v;
    m_lowerLeftCorner = origin - m_horizontal * 0.5f - m_vertical * 0.5f - focalDistance * m_w;

    m_lensRadius    = aperture / 2.0f;
}

//-------------------------------------------------------------------------
//
//
Ray ThinLens::getRay(float s, float t) const
{
    glm::vec2 random = m_lensRadius * rndPointUnitDisk();
    glm::vec3 offset = m_u * random.x + m_v * random.y;

    return Ray(m_origin + offset, 
        m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset);
}

//-------------------------------------------------------------------------
//
//
void ThinLens::printCamera()
{
    std::cout << "Thin Lens Camera" << std::endl;
    std::cout << "origin     : " << vecToString(m_origin) << std::endl;
}

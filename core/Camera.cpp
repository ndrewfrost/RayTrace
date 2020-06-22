/*
 * camera.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "camera.h"

///////////////////////////////////////////////////////////////////////////
// Camera                                                                //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
// Constructor
//
Camera::Camera(glm::vec3 origin, glm::vec3 lookAt, glm::vec3 vup, float hfov, float aspectRatio)
{
    float theta = degree2Rad(hfov);
    float width = tan(theta / 2.f);
    float viewportWidth = 2.f * width;
    float viewportHeight = aspectRatio * viewportWidth;

    glm::vec3 w = glm::normalize(origin - lookAt);
    glm::vec3 u = glm::normalize(glm::cross(vup, w));
    glm::vec3 v = glm::cross(w, u);

    m_origin = origin;
    m_horizontal = viewportWidth * u;
    m_vertical = viewportHeight * v;
    m_lowerLeftCorner = origin - m_horizontal * 0.5f - m_vertical * 0.5f - w;
}


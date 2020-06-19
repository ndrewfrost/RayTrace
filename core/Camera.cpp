/*
 * camera.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "camera.h"

#include "../cameras/pinhole.h"
 //#include "../cameras/thinlens.h"

///////////////////////////////////////////////////////////////////////////
// Camera                                                                //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
// Constructor
//
Camera::Camera(glm::vec3 origin, glm::vec3 lookAt, glm::vec3 vup, float hfov, float aspectRatio)
{
    float theta = degree2Rad(hfov);
    float width = tan(theta / 2);
    float viewportWidth = 2.0 * width;
    float viewportHeight = aspectRatio * viewportWidth;

    glm::vec3 w = glm::normalize(origin - lookAt);
    glm::vec3 v = glm::normalize(glm::cross(vup, w));
    glm::vec3 u = glm::cross(w, u);

    m_origin = origin;
    m_horizontal = viewportWidth * u;
    m_vertical = viewportHeight * v;
    m_lowerLeftCorner = origin - (m_horizontal / 2) - (m_vertical / 2) - w;
}

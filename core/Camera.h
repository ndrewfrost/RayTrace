/*
 * camera.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>
#include <utility>

#include "../common/glm_common.h"
#include "../common/math.h"

///////////////////////////////////////////////////////////////////////////
// Camera                                                                //
///////////////////////////////////////////////////////////////////////////

class Camera
{
public:
    Camera(glm::vec3 origin, glm::vec3 lookAt, glm::vec3 vup, float hfov, float aspectRatio);

    virtual ~Camera() = default;

    virtual void printCamera() = 0;

protected:
    glm::vec3 m_origin;
    glm::vec3 m_lowerLeftCorner;

    glm::vec3 m_horizontal;
    glm::vec3 m_vertical;
};

#endif // !CAMERA_H_

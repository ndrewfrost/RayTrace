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

#include "rapidjson/document.h"
using namespace rapidjson;

namespace rt {

///////////////////////////////////////////////////////////////////////////
// Camera                                                                //
///////////////////////////////////////////////////////////////////////////

class Camera
{
public:
    Camera() = default;

    static std::unique_ptr<Camera> createCamera(Value& cameraSpecs);

    virtual ~Camera() = default;

    virtual void printCamera() = 0;

    void generateLookMatrix();

protected:
    int height, width, fov;

    glm::vec3 location;
    glm::vec3 lookAt;

    glm::mat4 cameraToWorld;
};

} // namespace rt
 
#endif // !CAMERA_H_

/*
 * camera.cpp
 * Andrew Frost
 * 2020
 *
 */

#include "camera.h"

#include "../cameras/pinhole.h"
 //#include "../cameras/thinlens.h"

namespace rt {

///////////////////////////////////////////////////////////////////////////
// Camera                                                                //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
// Create a look at Matrix from camera position and look at vectors
//
void Camera::generateLookMatrix() {
    glm::vec3 dir = glm::normalize(location - lookAt);

    //vec3f(0,1,0) is up vector
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), dir)); 

    glm::vec3 up = glm::cross(dir, right);

    cameraToWorld[3][0] = location.x;
    cameraToWorld[3][1] = location.y;
    cameraToWorld[3][2] = location.z;

    cameraToWorld[0][0] = right.x;
    cameraToWorld[0][1] = right.y;
    cameraToWorld[0][2] = right.z;

    cameraToWorld[1][0] = up.x;
    cameraToWorld[1][1] = up.y;
    cameraToWorld[1][2] = up.z;

    cameraToWorld[2][0] = dir.x;
    cameraToWorld[2][1] = dir.y;
    cameraToWorld[2][2] = dir.z;

    cameraToWorld[0][3] = 0;
    cameraToWorld[1][3] = 0;
    cameraToWorld[2][3] = 0;
    cameraToWorld[3][3] = 1;
}

//-------------------------------------------------------------------------
// Create a camera object, either Pinhole or Thin lens
// Depending on the data from JSON in Value& CameraSpecs
//
std::unique_ptr<Camera> Camera::createCamera(Value& cameraSpecs)
{
    // check if defined cameratype
    if (!cameraSpecs.HasMember("type")) {
        std::cerr << "Camera type not specified" << std::endl;
        exit(-1);
    }

    const char* cameraType = cameraSpecs["type"].GetString();

    // Pinhole Camera
    if (strcmp(cameraType, "pinhole") == 0) {
        return std::make_unique<Pinhole>(Pinhole(cameraSpecs["width"].GetInt(),
                                                 cameraSpecs["height"].GetInt(),
                                                 cameraSpecs["fov"].GetInt(),
                                                 glm::vec3(cameraSpecs["location"][0].GetFloat(),
                                                           cameraSpecs["location"][1].GetFloat(),
                                                           cameraSpecs["location"][2].GetFloat()),
                                                 glm::vec3(cameraSpecs["look"][0].GetFloat(),
                                                           cameraSpecs["look"][1].GetFloat(),
                                                           cameraSpecs["look"][2].GetFloat())));
    }
    // Thin lens Camera
    else if (strcmp(cameraType, "thinlens") == 0) {
        std::cerr << "[thinlens] is yet to be implemented" << std::endl;
        exit(-1);
    }
    // Error
    else {
        std::cerr << "Camera type can either be: [pinhole] or [thinlens]" << std::endl;
        exit(-1);
    }
}

} // namespace rt
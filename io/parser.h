/*
 * parser.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <utility>
#include <iostream>

#include "../core/light.h"
#include "../core/geometry.h"
#include "../geometry/sphere.h"
#include "../core/camera.h"
#include "../cameras/pinhole.h"
#include "../core/scene.h"

#include "rapidjson/document.h"
using namespace rapidjson;

///////////////////////////////////////////////////////////////////////////
// Parser                                                                //
///////////////////////////////////////////////////////////////////////////

class Parser
{
public:
    static std::unique_ptr<Camera> readCamera(Value& value);

    static std::unique_ptr<Scene> readScene(Value& value);

    static std::shared_ptr<Geometry> readGeometry(Value& geometry);

    static glm::vec3 readVector(Value& value, std::string jsonLoc);

    static float readFloat(Value& value, std::string jsonLoc);

    static std::string readString(Value& value, std::string jsonLoc);
};



#endif // !PARSER_H_

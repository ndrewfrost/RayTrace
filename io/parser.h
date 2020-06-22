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
#include <unordered_map>

#include "../core/light.h"

#include "../core/camera.h"
#include "../cameras/pinhole.h"
#include "../cameras/thinlens.h"

#include "../core/geometry.h"
#include "../geometry/sphere.h"
#include "../core/scene.h"

#include "../core/material.h"
#include "../materials/normal.h"
#include "../materials/dielectric.h"
#include "../materials/lambertian.h"
#include "../materials/blinnphong.h"

#include "rapidjson/document.h"
using namespace rapidjson;

///////////////////////////////////////////////////////////////////////////
// Parser                                                                //
///////////////////////////////////////////////////////////////////////////

class Parser
{
    typedef std::unordered_map<std::string, std::shared_ptr<Material>> MaterialList;

public:
    static std::unique_ptr<Camera> readCamera(Value& value, float aspectRatio);

    static std::unique_ptr<Scene> readScene(Value& value);

    static void storeMaterial(MaterialList& sceneMaterials, Value& material);

    static std::shared_ptr<Material> readMaterial(Value& materials);

    static std::shared_ptr<Geometry> readGeometry(Value& geometry, MaterialList& sceneMaterials);

    static glm::vec3 readVector(Value& value, std::string jsonLoc);

    static float readFloat(Value& value, std::string jsonLoc);

    static std::string readString(Value& value, std::string jsonLoc);
};



#endif // !PARSER_H_

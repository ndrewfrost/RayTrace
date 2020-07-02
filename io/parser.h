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
#include "../lights/area.h"
#include "../lights/distant.h"
#include "../lights/infinitearea.h"
#include "../lights/spotlight.h"
#include "../lights/point.h"

#include "../core/camera.h"
#include "../cameras/pinhole.h"
#include "../cameras/thinlens.h"

#include "../core/geometry.h"
#include "../geometry/sphere.h"
#include "../geometry/triangle.h"
#include "../geometry/plane.h"
#include "../geometry/cone.h"
#include "../geometry/mesh.h"
#include "../geometry/box.h"
#include "../core/scene.h"

#include "../accelerators/aabb.h"
#include "../accelerators/bvh.h"

#include "../core/material.h"
#include "../materials/normal.h"
#include "../materials/dielectric.h"
#include "../materials/lambertian.h"
#include "../materials/blinnphong.h"
#include "../materials/orennayer.h"
#include "../materials/disney.h"
#include "../materials/gooch.h"
#include "../materials/emissive.h"

#include "rapidjson/document.h"
using namespace rapidjson;

///////////////////////////////////////////////////////////////////////////
// Settings                                                              //
///////////////////////////////////////////////////////////////////////////

struct Settings {
    unsigned int width;
    unsigned int height;
    unsigned int samples;
    bool bvh;

    Settings(unsigned int w, unsigned int h, unsigned int s, bool b) 
        : width(w), height(h), samples(s), bvh(b) {}
};

///////////////////////////////////////////////////////////////////////////
// Parser                                                                //
///////////////////////////////////////////////////////////////////////////

class Parser
{
private:
    typedef std::unordered_map<std::string, std::shared_ptr<Material>> MaterialList;

public:
    static std::shared_ptr<Settings> readSettings(Value& value);

    static std::unique_ptr<Camera> readCamera(Value& value, std::shared_ptr<Settings> settings);

    static std::unique_ptr<Scene> readScene(Value& value, std::shared_ptr<Settings> settings);

    static void storeMaterial(MaterialList& sceneMaterials, Value& material);

    static std::shared_ptr<Geometry> readGeometry(Value& geometry, MaterialList* sceneMaterials);
    
    static std::shared_ptr<Material> readMaterial(Value& materials);

    static std::shared_ptr<Light> readLight(Value& light);

    static glm::vec3 readVector(Value& value, std::string jsonLoc);

    static float readFloat(Value& value, std::string jsonLoc);

    static std::string readString(Value& value, std::string jsonLoc);
};

#endif // !PARSER_H_
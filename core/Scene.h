/*
 * scene.h
 * Andrew Frost
 * December 2019
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"
using namespace rapidjson;

class Scene {
public:
    void createScene(Value& sceneSpecs);
private:
};

#endif // !SCENE_H_

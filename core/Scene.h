/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "core/LightSource.h"
#include "lights/AreaLight.h"
#include "lights/PointLight.h"
#include "core/Shape.h"
#include "math/geometry.h"
#include "shapes/Sphere.h"
#include "shapes/Triangle.h"
#include "shapes/TriMesh.h"
#include "shapes/Plane.h"
#include "core/Material.h"
#include "materials/BlinnPhong.h"


using namespace rapidjson;

namespace rt {

    class Scene {
    public:

        Scene() {};

        void createScene(Value& scenespecs);

        void readBackgroundColor(Value& scenespecs);

        void readLights(Value& lights);

        Shape* readShape(Value& shapes);

        BlinnPhong readMaterial(Value& material);

        Vec3f readVec3f(Value& values, char* jsonLocation);

        Vec2f readVec2f(Value& val, char* jsonLocation);

        Vec3f getBackgroundColor() const {
            return backgroundColor;
        }
        std::vector<LightSource*>& getLightSources() {
            return lightSources;
        }

        std::vector<Shape*>& getShapes() {
            return  shapes;
        }
    private:

        std::vector<LightSource*> lightSources;
        std::vector<Shape*> shapes;
        Vec3f backgroundColor;

    };

} //namespace rt



#endif /* SCENE_H_ */

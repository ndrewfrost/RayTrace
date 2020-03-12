/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Material.h"
#include "materials/BlinnPhong.h"
#include <vector>
#include <math.h>

namespace rt {

    class Shape {
    public:

        Shape() {};
        virtual ~Shape() {};
        virtual Hit intersect(Ray) = 0;

        virtual BlinnPhong getMaterial() const { return material; };

        virtual bool hasTexture() = 0;

        virtual Vec3f getColor(Vec3f& hitPoint) { return Vec3f(); };

        virtual Vec3f getRandomPosition() {
            return Vec3f();
        }
        virtual Vec3f getJitteredPosition(Vec2i& samples, Vec2i& s) {
            return Vec3f();
        }

        virtual Vec3f* getVertices() { return NULL; }

        virtual int getVerticesSize() { return 0; }

    protected:
        BlinnPhong material;

    };


} //namespace rt


#endif /* SHAPE_H_ */

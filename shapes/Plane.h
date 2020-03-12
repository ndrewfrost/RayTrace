/*
 * Plane.h
 *
 *
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "materials/BlinnPhong.h"
#include "parsers/PPMWriter.h"

namespace rt {

    class Plane : public Shape {

    public:
        Plane(Vec3f point[4], Vec3f normal, BlinnPhong material, std::string textureLocation) :
            point{ point[0],point[1],point[2], point[3] },
            normal(normal),
            material(material),
            textureLocation(textureLocation),
            texBool(true) {

            PPMWriter::imageReader(texture, textureLocation, texWidth, texHeight);
            horLine = (point[0] - point[3]);
            verLine = (point[0] - point[1]);
            planeWidth = horLine.length();
            planeHeight = verLine.length();
        };

        Plane(Vec3f point[4], Vec3f normal, BlinnPhong material) : point{ point[0],point[1],point[2], point[3] }, normal(normal), material(material), texBool(false) {
            horLine = (point[0] - point[3]);
            verLine = (point[0] - point[1]);
            planeWidth = horLine.length();
            planeHeight = verLine.length();
        };


        ~Plane() {};

        Hit intersect(Ray ray);
        BlinnPhong getMaterial() const { return material; };

        bool hasTexture() { return texBool; };

        int getTextureColor(Vec3f& pointHit);

        Vec3f getColor(Vec3f& pointHit) {
            int c = 0;
            c = getTextureColor(pointHit);
            return texture[c];
        };

        Vec3f getRandomPosition();

        Vec3f getJitteredPosition(Vec2i& samples, Vec2i& s);

        Vec3f* getVertices() { return point; }
        int getVerticesSize() { return 4; }

    private:
        uint32_t planeWidth, planeHeight;

        Vec3f point[4];
        Vec3f normal;

        Vec3f horLine, verLine;

        BlinnPhong material;

        std::string textureLocation;
        Vec3f* texture;
        int texWidth, texHeight;
        bool texBool;
    };



} //namespace rt




#endif /* TRIANGLE_H_ */

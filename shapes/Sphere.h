/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "core/Shape.h"
#include "parsers/PPMWriter.h"

namespace rt {

    class Sphere : public Shape {

    public:

        //
        // Constructors
        //
        Sphere(Vec3f center, float radius, BlinnPhong material) : center(center), radius(radius), material(material), texBool(false) {};

        Sphere(Vec3f center, float radius, BlinnPhong material, std::string textureLocation) :
            center(center),
            radius(radius),
            material(material),
            textureLocation(textureLocation),
            texBool(true) {
            PPMWriter::imageReader(texture, textureLocation, texWidth, texHeight);
        };

        ~Sphere() {};

        Hit intersect(Ray ray);

        int getTextureColor(Vec3f& pointHit);

        Vec3f getColor(Vec3f& pointHit) {
            int c = 0;
            c = getTextureColor(pointHit);
            return texture[c];
        };

        BlinnPhong getMaterial() const { return material; }

        bool hasTexture() {
            return texBool;
        }


        // Get top bottom, side and from points for shere BVH
        void getPoint(float angleX, float angleY, Vec3f& point) {

            angleX = angleX / 180 * atan(1) * 4;
            angleY = angleY / 180 * atan(1) * 4;

            point.x = (radius * cos(angleX) * sin(angleY));
            if (fabs(point.x) < 0.00001f) point.x = 0;
            point.x = point.x + center.x;

            point.y = (radius * sin(angleX) * sin(angleY));
            if (fabs(point.y) < 0.00001f) point.y = 0;
            point.y = point.y + center.y;

            point.z = (radius * cos(angleY));
            if (fabs(point.z) < 0.00001f) point.z = 0;
            point.z = point.z + center.z;
        }

        Vec3f* getVertices() {
            Vec3f points[6];
            getPoint(0, 90, points[0]);
            getPoint(90, 90, points[1]);
            getPoint(180, 90, points[2]);
            getPoint(270, 90, points[3]);
            getPoint(0, 0, points[4]);
            getPoint(90, 180, points[5]);
            return points;
        }

        int getVerticesSize() { return 6; }

    private:
        Vec3f center;
        float radius;

        BlinnPhong material;

        std::string textureLocation;
        bool texBool;
        int texWidth, texHeight;
        Vec3f* texture;

        const double PI = 3.141592653589793;
    };



} //namespace rt




#endif /* SPHERE_H_ */

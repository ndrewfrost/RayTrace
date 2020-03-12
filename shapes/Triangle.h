/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "materials/BlinnPhong.h"
#include "parsers/PPMWriter.h"

namespace rt {

    class Triangle : public Shape {

    public:
        Triangle(Vec3f point[3], Vec3f normal, BlinnPhong material, std::string textureLocation) :
            point{ point[0],point[1],point[2] }, 
            normal(normal),
            material(material),
            textureLocation(textureLocation),
            texBool(true){

            PPMWriter::imageReader(texture, textureLocation, texWidth, texHeight);

            horLine = (point[0] - point[2]);
            verLine = (point[0] - point[1]);

            triWidth = horLine.length();
            triHeight = verLine.length();
        };

        Triangle(Vec3f point[3], Vec3f normal, BlinnPhong material) :
            point{ point[0],point[1],point[2] },
            normal(normal),
            material(material),
            texBool(false){
        
            horLine = (point[0] - point[2]);
            verLine = (point[0] - point[1]);

            triWidth = horLine.length();
            triHeight = verLine.length(); 
        };

        ~Triangle() {};

        Hit intersect(Ray ray);

        BlinnPhong getMaterial() const { return material; };

        bool hasTexture() { return texBool; };

        int getTextureColor(Vec3f& pointHit);

        Vec3f getColor(Vec3f& pointHit) {
            int c = 0;
            c = getTextureColor(pointHit);
            return texture[c];
        };

    private:
        uint32_t triWidth, triHeight;

        Vec3f point[3];
        Vec3f normal;   

        Vec3f horLine, verLine;

        BlinnPhong material;

        std::string textureLocation;
        Vec3f* texture;
        bool texBool;
        int texWidth, texHeight;
    };



} //namespace rt




#endif /* TRIANGLE_H_ */

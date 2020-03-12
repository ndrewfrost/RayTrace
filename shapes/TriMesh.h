/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "shapes/Triangle.h"
#include "materials/BlinnPhong.h"
#include "parsers/PPMWriter.h"

namespace rt {

    class TriMesh : public Shape {
    public:

        TriMesh(int size, BlinnPhong material) : size(size) , material(material) {};

        
        ~TriMesh() {
            for (auto f : faces) {
                delete f;
            }
        };

        void addVertex(Vec3f & v);
        void addNormal(int n);

        bool addFace(int a, int b, int c);
                
        Hit intersect(Ray ray);

        bool hasTexture() {
            return false;
        }

        BlinnPhong getMaterial() const { return material; };

        Vec3f* getVertices() { return &vertices[0]; }
        int getVerticesSize() { return vertices.size(); }
    private:
        std::vector<int> normals;
        std::vector<Vec3f> vertices;
        std::vector<Triangle*> faces;
        BlinnPhong material;

        int face = 0;
        int size = 0;


    };



} //namespace rt




#endif /* TRIMESH_H_ */

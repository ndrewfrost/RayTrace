/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"


namespace rt {

    void TriMesh::addVertex(Vec3f& v)
    {
        vertices.emplace_back(v);
    }

    void TriMesh::addNormal(int n)
    {
        normals.emplace_back(n);
    }

    bool TriMesh::addFace(int a, int b, int c)
    {
        int vSize = vertices.size();

        if (a >= vSize || b >= vSize || c >= vSize) {
            return false;
        }
        Vec3f point[3];
        point[0] = vertices.at(a);
        point[1] = vertices.at(b);
        point[2] = vertices.at(c);

        if ((point[1] - point[0]).length() == 0) return false;
        if ((point[2] - point[1]).length() == 0) return false;
        if ((point[0] - point[2]).length() == 0) return false;

        Vec3f e = point[0] - point[1];
        Vec3f e2 = point[0] - point[2];
        Vec3f normal = e.crossProduct(e2).normalize();

        if (normals.size() > 0) {
            if (normals.at(a) == -1) {
                normal = -normal;
            }
        }

        Triangle* triangle = new Triangle(point, normal, material);

        faces.emplace_back(triangle);

        return true;

    }

    Hit TriMesh::intersect(Ray ray)
    {
        Hit* hits = new Hit[faces.size()];
        Hit* hit = hits;
        Hit closest;

        for (int s = 0; s < faces.size(); s++) {
            *hit = faces.at(s)->intersect(ray);
            if (hit->hit) {
                if (closest.hit) {
                    if (closest.distance <= hit->distance) {
                        closest = *hit;
                        face = s;
                    }
                }
                else {
                    closest = *hit;
                    face = s;
                }
            }
            hit++;
        }

        delete[] hits;
        return closest;
    }

} //namespace rt



/*
 * BVH.h
 *
 */


#ifndef BVH_H_
#define BVH_H_

#include "core/Shape.h"

namespace rt {

    // Bounding Box
    class BBox
    {
    public:

        BBox();

        ~BBox() {
            delete[] bound;
        }

        BBox(Vec3f lower, Vec3f upper) {
            bound[0] = upper;
            bound[1] = lower;
        }

        void extendBox(Vec3f& point) {
            // check if point is less than lower bound
            if (point.x < bound[0].x) bound[0].x = point.x;
            if (point.y < bound[0].y) bound[0].y = point.y;
            if (point.z < bound[0].z) bound[0].z = point.z;

            // check if point is greater than upper bound
            if (point.x > bound[1].x) bound[1].x = point.x;
            if (point.y > bound[1].y) bound[1].y = point.y;
            if (point.z > bound[1].z) bound[1].z = point.z;

        }

        Vec3f centre() {
            Vec3f centre = bound[0] + bound[1];
            centre.x = centre.x / 2;
            centre.y = centre.y / 2;
            centre.z = centre.z / 2;
            return centre;
        }

        void surround(Shape** shapes, int numShapes) {
            for (int s = 0; s < numShapes; s++) {
                Vec3f* vec = shapes[s]->getVertices();
                for (int v = 0; v < shapes[s]->getVerticesSize(); v++) {
                    extendBox(vec[v]);
                }
            }
        };


        // Check if ray intersects bounding box
        int intersect(Ray r) {

            Vec3f individualDir;
            individualDir.x = 1 / r.direction.x;
            individualDir.y = 1 / r.direction.y;
            individualDir.z = 1 / r.direction.z;

            int signX = (individualDir.x < 0);
            int signY = (individualDir.y < 0);
            int signZ = (individualDir.z < 0);

            float tmin, tmax, tymin, tymax, tzmin, tzmax;

            tmin = (bound[signX].x - r.origin.x) * individualDir.x;
            tmax = (bound[1 - signX].x - r.origin.x) * individualDir.x;

            tymin = (bound[signY].y - r.origin.y) * individualDir.y;
            tymax = (bound[1 - signY].y - r.origin.y) * individualDir.y;

            if ((tmin > tymax) || (tymin > tmax)) return -1;
            if (tymin > tmin) tmin = tymin;
            if (tymax < tmax) tmax = tymax;

            tzmin = (bound[signZ].z - r.origin.z) * individualDir.z;
            tzmax = (bound[1 - signZ].z - r.origin.z) * individualDir.z;

            if ((tmin > tzmax) || (tzmin > tmax)) return -1;
            if (tzmin > tmin) tmin = tzmin;
            if (tzmax < tmax) tmax = tzmax;

            float t = tmin;
            if (t < 0) {
                t = tmax;
                if (t < 0) return -1;
            }

            return t;
        }

    public:
        Vec3f bound[2];
    };





    // BVH class
    class BVH : public Shape {

    public:
        BVH(Shape** shapes, int numShapes, int axis);

        int qsplit(Shape** shapes, int numShapes, float pivotAxis, int axis);

        Shape* buildBranch(Shape** shapes, int numShapes, int axis);

        ~BVH() {
            delete[] child;
        };

        Hit intersect(Ray);
        bool hasTexture();

    private:
        BBox bbox;
        Shape* child[2];
        int splitAxis;
    };



} //namespace rt



#endif /* BVH_H_ */

/*
 * BVH.cpp
 *
 
 

#include "BVH.h"


namespace rt {

    BVH::BVH(Shape** shapes, int numShapes, int axis) {

        if (numShapes == 1) {
            child[0] = shapes[0];
            child[1] = shapes[0];
            splitAxis = axis;
            return;
        }

        if (numShapes == 2) {
            child[0] = shapes[0];
            child[1] = shapes[1];
            splitAxis = axis;
            return;
        }

        // surround objects with bounding box
        bbox.surround(shapes, numShapes);
        Vec3f pivot = bbox.centre();

        // split primitives and say where the end of left node is
        int midPoint = qsplit(shapes, numShapes, pivot[axis], axis);

        //create new BV
        int nextAxis = (axis + 1) % 3;
        child[0] = buildBranch(shapes, midPoint, nextAxis);
        child[1] = buildBranch(&shapes[midPoint], numShapes - midPoint, nextAxis);
    }

    int BVH::qsplit(Shape** shapes, int numShapes, float pivotAxis, int axis) {
        
        Shape** left;
        Shape** right;
        int rightCount = numShapes;
        int leftCount = 0;

        Vec3f* vec;

        int position = numShapes;

        bool leftBool = true;
        //for all shapes
        for (int s = 0; s < numShapes; ++s) {
            vec = shapes[s]->getVertices();
            //check each vertex
            for (int v = 0; v < shapes[s]->getVerticesSize(); v++) {
                // if one is right of axis
                if (vec[s][axis] > pivotAxis) {
                    leftBool = false;
                }
            }

            //Make a lsit of left shapes
            if (left) {
                *(left++) = shapes[s];
                leftCount++;
            }
            //Make a list of right shapes
            else {
                *(right++) = shapes[s];
                rightCount--;
            }
            leftBool = true;
        }

        // Put shapes into list
        for (int l = 0; l < leftCount; l++) {
            shapes[l] = left[l];
        }

        for (int r = rightCount; r < numShapes; r++) {
            shapes[r] = right[r];
        }

        return position;
    }
    
    Shape* BVH::buildBranch(Shape** shapes, int numShapes, int axis) {
        BVH* bvh = new BVH();
        if (numShapes == 1) {
            return shapes[0];
        }

        if (numShapes == 2) {
            bvh->child[0] = shapes[0];
            bvh->child[1] = shapes[1];
            bvh->splitAxis = axis;
            return bvh;
        }

        // surround objects with bounding box
        bvh->bbox.surround(shapes, numShapes);
        Vec3f pivot = bbox.centre();

        // split primitives and say where the end of left node is
        int midPoint = qsplit(shapes, numShapes, pivot[axis], axis);

        //create new BV
        int nextAxis = (axis + 1) % 3;
        bvh->child[0] = buildBranch(shapes, midPoint, nextAxis);
        bvh->child[1] = buildBranch(&shapes[midPoint], numShapes - midPoint, nextAxis);

        return bvh;
    }
    

    // Intersect
    Hit BVH::intersect(Ray ray)
    {
        Hit hit;

        float t = bbox.intersect(ray);
        if (t == -1) {
            hit.hit = false;
            return hit;
        }

        hit.distance = t;

        Hit hit1 = child[0]->intersect(ray);
        Hit hit2 = child[1]->intersect(ray);

        if (hit1.hit && hit1.distance < hit2.distance) {
            return hit1;
        }
        else if(hit2.hit && hit1.distance >= hit2.distance) {
            return hit2;
        }

        else {
            hit.hit = false;
            return hit;
        }
    }

    bool BVH::hasTexture()
    {
        return false;
    }

} //namespace rt

*/

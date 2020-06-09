/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"

namespace rt{

    /**
     * Computes whether a ray hit the specific instance of a triangle shape and returns the hit data
     *
     * @param ray cast ray to check for intersection with shape
     *
     * @return hit struct containing intersection information
     *
     */
    Hit Triangle::intersect(Ray ray)
    {
        Hit h;

        Vec3f center = point[0] + point[1] + point[2];
        center.x /= 3;
        center.y /= 3;
        center.z /= 3;

        float denom = normal.dotProduct(ray.direction);
        if (fabs(denom) > 0.0001f) {
            float t = (center - ray.origin).dotProduct(normal) / denom;
            if (t < 0) {
                h.hit = false;
                return h;
            }

            Vec3f pointHit = ray.origin + ray.direction * t;

            Vec3f edge = point[1] - point[0];
            Vec3f v = pointHit - point[0];
            if (normal.dotProduct(edge.crossProduct(v)) < 0) {
                h.hit = false;
                return h;
            }

            edge = point[2] - point[1];
            v = pointHit - point[1];
            if (normal.dotProduct(edge.crossProduct(v)) < 0) {
                h.hit = false;
                return h;
            }

            edge = point[0] - point[2];
            v = pointHit - point[2];
            if (normal.dotProduct(edge.crossProduct(v)) < 0) {
                h.hit = false;
                return h;
            }
           
                h.backSurface = false;
            
            h.hit = true;
            h.hitPoint = pointHit;
            h.surfaceNormal = normal;
            h.surfaceNormal.normalize();
            h.viewDirection = -(ray.direction - ray.origin);
            h.viewDirection.normalize();
            h.distance = ray.origin.dotProduct(pointHit);
            return h;
        }
        h.hit = false;
        return h;
    }

    int Triangle::getTextureColor(Vec3f& hitPoint)
    {
        
        Vec3f hor = -horLine;
        hor.normalize();
        Vec3f ver = -verLine;
        ver.normalize();
        Vec3f h = hitPoint - point[0];

        float u = h.dotProduct(hor) / triWidth;
        float v = h.dotProduct(ver) / triHeight;

        int width = (u * texWidth);
        int height = (v * texHeight);

        int pixel = 0;
        if (height > 0) {
            pixel = (height - 1) * texHeight + width;
        }
        else {
            pixel = width;
        }
        // Get the color from the get_array 
        return pixel;
    }
} //namespace rt

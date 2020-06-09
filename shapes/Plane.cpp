/*
 * Plane.cpp
 *
 *
 */
#include "Plane.h"



namespace rt {

    /**
         * Computes whether a ray hit the specific instance of a plane shape and returns the hit data
         *
         * @param ray cast ray to check for intersection with shape
         *
         * @return hit struct containing intersection information
         *
         */
    Hit Plane::intersect(Ray ray) {

        Hit h;

        Vec3f center = point[0] + point[1] + point[2] + point[3];
        center.x /= 4;
        center.y /= 4;
        center.z /= 4;

        float denom = normal.dotProduct(ray.direction);
        if (fabs(denom) > 0.0001f) {
            float t = (center - ray.origin).dotProduct(normal) / denom;
            if (t < 0) {
                h.hit = false;
                return h;
            }

            Vec3f pointHit = ray.origin + ray.direction * t;
            Vec3f v = point[0] - pointHit;

            float projection1 = 0, projection2 = 0;

            if (planeWidth > 0) {
                projection1 = v.dotProduct(horLine) / planeWidth;
            }
            if (planeHeight > 0) {
                projection2 = v.dotProduct(verLine) / planeHeight;
            }
            if ((projection1 < planeWidth && projection1 > 0)
                && (projection2 < planeHeight && projection2 > 0)) {

                if (denom > 0) {
                    h.backSurface = true;
                }

                h.hit = true;
                h.hitPoint = pointHit;
                h.surfaceNormal = normal.normalize();
                h.viewDirection = (ray.direction - ray.origin).normalize();
                h.distance = ray.origin.dotProduct(pointHit);
                return h;
            }
        }
        h.hit = false;
        return h;
    }

    int Plane::getTextureColor(Vec3f& hitPoint)
    {
        Vec3f hor = -horLine;
        hor.normalize();
        Vec3f ver = -verLine;
        ver.normalize();
        Vec3f h = hitPoint - point[0];

        float u = h.dotProduct(hor) / planeWidth;
        float v = h.dotProduct(ver) / planeHeight;

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

    Vec3f Plane::getRandomPosition()
    {
        float u = randomMath::random(0, planeWidth);
        float v = randomMath::random(0, planeHeight);

        Vec3f hor = horLine;
        hor.normalize();
        Vec3f ver = verLine;
        ver.normalize();

        Vec3f randomPoint = point[0] - (u * hor + v * ver);
        //randomPoint.y = -randomPoint.y;
        return randomPoint;
    }

    Vec3f Plane::getJitteredPosition(Vec2i& samples, Vec2i& s)
    {
        float u = randomMath::random(0.1, 0.9);
        float v = randomMath::random(0.1, 0.9);

        u = ((s.x + u) / samples.x) * planeWidth;
        v = ((s.y + v) / samples.y) * planeHeight;

        Vec3f hor = horLine;
        hor.normalize();
        Vec3f ver = verLine;
        ver.normalize();

        Vec3f randomPoint = point[0] - (u * hor + v * ver);
        //randomPoint.y = -randomPoint.y;
        return randomPoint;
    }


} //namespace rt

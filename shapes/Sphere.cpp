/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


namespace rt {

    bool solveQuadratic(const float& a, const float& b, const float& c, float& t0, float& t1)
    {
        float discr = b * b - 4 * a * c;
        if (discr < 0) return false;

        else if (discr == 0) {
            t0 = t1 = -0.5 * b / a;
        }
        else {
            float q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
            t0 = q / a;
            t1 = c / q;
        }

        return true;
    }

    /**
     * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
     *
     * @param ray cast ray to check for intersection with shape
     *
     * @return hit struct containing intersection information
     *
     */
    Hit Sphere::intersect(Ray ray) {

        Hit h;

        Vec3f rayToCentre = ray.origin - center;
        float t0, t1;
        float a = ray.direction.dotProduct(ray.direction);
        float b = 2 * rayToCentre.dotProduct(ray.direction);
        float c = rayToCentre.dotProduct(rayToCentre) - (radius * radius);
        if (!solveQuadratic(a, b, c, t0, t1)) {
            h.hit = false;
            return h;
        }

        if (t0 > t1) {
            std::swap(t0, t1);
        }

        if (t0 < 0) {
            t0 = t1;
            if (t0 < 0) {
                h.hit = false;
                return h;
            }
        }

        float t = t0;

        h.hit = true;
        Vec3f pointHit = ray.origin + ray.direction * t;
        h.hitPoint = pointHit;
        h.surfaceNormal = (pointHit - center);
        h.surfaceNormal.normalize();
        h.viewDirection = -(ray.direction - ray.origin);
        h.viewDirection.normalize();
        h.distance = ray.origin.dotProduct(pointHit);

        return h;

    }

    int Sphere::getTextureColor(Vec3f& pointHit)
    {

        Vec3f surfaceNormal = (pointHit - center);
        surfaceNormal.normalize();

        double u = 0.5 + atan2(surfaceNormal[0], surfaceNormal[2]) / (2 * PI);
        double v = 0.5 - asin(surfaceNormal[1]) / PI;

        int width = u * texWidth;
        int height = v * texHeight;

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



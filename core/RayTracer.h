/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Camera.h"
#include "cameras/ThinLens.h"
#include "core/Scene.h"
#include "core/Shape.h"
#include "core/LightSource.h"
#include <math.h>
#include <random>
#include <iostream>

namespace rt{



    /*
     * Raytracer class declaration
     */
    class RayTracer {
    public:

	    RayTracer();

	    static Vec3f* render(Camera* camera, Scene* scene, int nbounces, std::string sampling, Vec2i nsamples);
        static Vec3f* tonemap(Vec3f* pixelbuffer, uint32_t width, uint32_t height);
        static void antiTonemap(Vec3f& pixelbuffer);


    private:
        static Vec3f castRay(Vec3f& origin, Vec3f& direction, std::vector<Shape*>& shapes, std::vector<LightSource*>& lights, Vec3f& backgroundColor, RayType rayType, int nbounces);
        
        static Hit traceRay(Ray& ray, std::vector<Shape*>& shapes, std::vector<LightSource*>& lights, int light);

    };




} //namespace rt



#endif /* RAYTRACER_H_ */


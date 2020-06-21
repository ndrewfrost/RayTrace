/*
 * raytracer.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <memory>
#include "camera.h"
#include "scene.h"
#include "../io/display.h"
#include "ray.h"

///////////////////////////////////////////////////////////////////////////
// RayTracer                                                             //
///////////////////////////////////////////////////////////////////////////

class RayTracer {
    
public:
    RayTracer(std::shared_ptr<Camera>       camera, 
              std::shared_ptr<Scene>        scene, 
              std::shared_ptr<DisplayImage> output);
   
    ~RayTracer() = default;

    void render();

    glm::vec3 rayColor(const Ray& r, int depth);

private:
    std::shared_ptr<Camera>       m_camera = nullptr;
    std::shared_ptr<Scene>        m_scene  = nullptr;
    std::shared_ptr<DisplayImage> m_output = nullptr;
};

#endif // !RAYTRACER_H_

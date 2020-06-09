/*
 * raytracer.h
 * Andrew Frost
 * December 2019
 *
 */

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

class RayTracer {
public:
    RayTracer(Camera* camera, Scene* scene);
    ~RayTracer();

    bool finisedRender();

private:
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Scene> scene;
    bool rendered;
};

#endif // !RAYTRACER_H_

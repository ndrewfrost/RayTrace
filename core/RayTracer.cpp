/*
 * raytracer.h
 * Andrew Frost
 * 2020
 *
 */

#include "raytracer.h"

///////////////////////////////////////////////////////////////////////////
// Ray Tracer                                                            //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
//
//
RayTracer::RayTracer(std::shared_ptr<Camera> camera, 
                     std::shared_ptr<Scene> scene,
                     std::shared_ptr<DisplayImage> output)
{
    m_camera = camera;
    m_scene  = scene;
    m_output = output;
}

//-------------------------------------------------------------------------
//
//
void RayTracer::render()
{
    for (unsigned int y = 0; y < m_output->getHeight(); ++y) {
        for (unsigned int x = 0; x < m_output->getWidth(); ++x) {

            float u = (x + random()) / m_output->getWidth();
            float v = (y + random()) / m_output->getHeight();

            Ray r = m_camera->getRay(u, v);

            glm::vec3 pixelColor = rayColor(r);

            m_output->setPixel(x, y, pixelColor);
        }
    }
}

//-------------------------------------------------------------------------
//
//
glm::vec3 RayTracer::rayColor(const Ray& r)
{
    HitRecord record;
    // TODO Material Color, Currently Renders Normals
    if (m_scene->intersect(r, 0, infinity, record)) {
        return 0.5f * (record.normal + glm::vec3(1.0, 1.0, 1.0));
    }

    // Background color
    glm::vec3 unitDir = glm::normalize(r.direction());
    float t = 0.5f * (unitDir.y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.3f, 0.4f, 0.8f);
}
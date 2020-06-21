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
 // Constructor
 //
RayTracer::RayTracer(std::shared_ptr<Camera> camera,
    std::shared_ptr<Scene>                   scene,
    std::shared_ptr<DisplayImage>            output)
{
    m_camera = camera;
    m_scene = scene;
    m_output = output;
}

//-------------------------------------------------------------------------
// Render the frame via raytracing
//
void RayTracer::render()
{
    for (unsigned int y = 0; y < m_output->getHeight(); ++y) {
        std::cerr << "\rProgression: " << (y + 1) << " " << std::flush;
        for (unsigned int x = 0; x < m_output->getWidth(); ++x) {
            // Multi Sampling
            glm::vec3 pixelColor(0.f);
            for (unsigned int s = 0; s < m_output->getNumberSamples(); ++s) {
                float u = (x + randomFloat()) / m_output->getWidth();
                float v = (y + randomFloat()) / m_output->getHeight();

                Ray r = m_camera->getRay(u, v);

                pixelColor += rayColor(r, 50);
            }

            m_output->setPixel(x, y, pixelColor);
        }
    }
}

//-------------------------------------------------------------------------
// Color the ray
//
glm::vec3 RayTracer::rayColor(const Ray& r, int depth)
{
    HitRecord record;
    // ray bound limit
    if (depth <= 0)
        return glm::vec3(0.f, 0.f, 0.f);

    // Collect light
    if (m_scene->intersect(r, 0.001f, infinity, record)) {
        //return 0.5f * (record.normal + glm::vec3(1.0, 1.0, 1.0));
        glm::vec3 bounceDir = record.point + record.normal + rndPointUnitSphere();
        return 0.5f * rayColor(Ray(record.point, bounceDir - record.point), depth - 1);

    }

    // Background color
    glm::vec3 unitDir = glm::normalize(r.direction());
    float t = 0.5f * (unitDir.y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.3f, 0.4f, 0.8f);
}
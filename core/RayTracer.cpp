/*
 * raytracer.h
 * Andrew Frost
 * 2020
 *
 */

#include "raytracer.h"

///////////////////////////////////////////////////////////////////////////
// Ray Tracing                                                           //
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
// Constructor
//
RayTracer::RayTracer(std::shared_ptr<Camera>       camera, 
                     std::shared_ptr<Scene>        scene,
                     std::shared_ptr<DisplayImage> output)
{
    m_camera = camera;
    m_scene  = scene;
    m_output = output;
}

//-------------------------------------------------------------------------
// Render the frame via raytracing
//
void RayTracer::render()
{
    for (unsigned int y = 0; y < m_output->getHeight(); ++y) {
        std::cerr << "\rProgression: " << (y+1) << " " << std::flush;
        for (unsigned int x = 0; x < m_output->getWidth(); ++x) {            
            // Multi Sampling
            glm::vec3 pixelColor(0.f);            
            for (unsigned int s = 0; s < m_output->getNumberSamples(); ++s) {
                float u = (x + randomFloat()) / m_output->getWidth();
                float v = (y + randomFloat()) / m_output->getHeight();

                Ray r = m_camera->getRay(u, v);

                pixelColor += trace(r, 50);
            }

            m_output->setPixel(x, y, pixelColor);
        }
    }
}

//-------------------------------------------------------------------------
// Color the ray
//
glm::vec3 RayTracer::trace(const Ray& ray, int depth)
{
    // ray bounce limit
    if (depth <= 0)
        return glm::vec3(0.f, 0.f, 0.f);

    // ray hit nothing, return background colour / Black
    HitRecord record;
    if (!m_scene->intersectGeometry(ray, 0.001f, infinity, record))
        return glm::vec3(0.02f, 0.02f, 0.02f);

    // Emissive Material    
    if (record.material->emits())
        return record.material->emitted(); // Hit an area light
    
    Ray rayOut;

    // Light Indirect
    glm::vec3 sample = record.material->sample(ray, rayOut, record);

    glm::vec3 indirect = sample * trace(rayOut, depth - 1)
                                * glm::dot(record.normal, rayOut.direction())
                                / record.material->pdf(ray, rayOut);

    // Sample a light
    //if(m_scene->sampleLight(hitPoint, rayOut))
    // Light Direct
    //glm::vec3 direct(0.f);
    //glm::vec3 bsdf(0.f);
    //glm::vec3 direct = bsdf * glm::dot(record.normal, ) 
    //                 * glm::dot(record.normal, rayOut.direction())
    //                 / record.material->pdf(ray, rayOut);
    
    return indirect;
}

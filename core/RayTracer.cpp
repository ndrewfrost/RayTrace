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
    float t = m_scene->m_objects[0]->intersect(r);
    if (t > 0.0f) {
        glm::vec3 normal = glm::normalize(r.at(t) - glm::vec3(0.f, 0.f, -1.f));
        return 0.5f * glm::vec3(normal.x + 1.f, normal.y + 1.f, normal.z + 1.f);
    }

    glm::vec3 unitDir = glm::normalize(r.direction());
    t = 0.5f * (unitDir.y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}
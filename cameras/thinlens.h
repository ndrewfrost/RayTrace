/*
 * thinlens.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "../core/ray.h"
#include "../core/camera.h"


 ///////////////////////////////////////////////////////////////////////////
 // Thin Lens                                                             //
 ///////////////////////////////////////////////////////////////////////////

class ThinLens : public Camera
{
public:
    ThinLens(glm::vec3 origin, glm::vec3 lookAt, glm::vec3 vup, float hfov,
        float aspectRatio, float aperture, float focalDistance);

    ~ThinLens() = default;

    Ray getRay(float s, float t) const;

    void printCamera();

private:
    glm::vec3 m_u, m_v, m_w;
    float     m_lensRadius;
};



#endif // !THINLENS_H_

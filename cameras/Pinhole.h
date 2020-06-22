/*
 * pinhole.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "../core/ray.h"
#include "../core/camera.h"


///////////////////////////////////////////////////////////////////////////
// Pinhole                                                               //
///////////////////////////////////////////////////////////////////////////

class Pinhole : public Camera
{
public:
    Pinhole(glm::vec3 origin, glm::vec3 lookAt, glm::vec3 vup, float hfov, float aspectRatio)
        : Camera(origin, lookAt, vup, hfov, aspectRatio) {}
    
    ~Pinhole() = default;

    Ray getRay(float u, float v) const;

    void printCamera();
    
private:

};



#endif // !PINHOLE_H_

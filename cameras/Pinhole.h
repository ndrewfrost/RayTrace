/*
 * pinhole.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "../core/camera.h"
#include "../core/ray.h"

 ///////////////////////////////////////////////////////////////////////////
 // Pinhole                                                               //
 ///////////////////////////////////////////////////////////////////////////

class Pinhole : public Camera
{
public:
    Pinhole(glm::vec3 origin, glm::vec3 lookAt, glm::vec3 vup, float hfov, float aspectRatio);

    ~Pinhole() = default;

    Ray getRay(float s, float t) const;

    void printCamera();

private:

};



#endif // !PINHOLE_H_

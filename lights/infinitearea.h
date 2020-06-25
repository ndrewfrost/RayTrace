/*
 * infinitearea.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef INFINITEAREALIGHT_H_
#define INFINITEAREALIGHT_H_

#include "../core/light.h"

///////////////////////////////////////////////////////////////////////////
// Infinite Area Light                                                   //
///////////////////////////////////////////////////////////////////////////

class InfiniteAreaLight : public Light {
public:
    InfiniteAreaLight()  = default;

    ~InfiniteAreaLight() = default;

    virtual glm::vec3 sampleLight(glm::vec3 dest) {
        return glm::vec3(0);
    }

private:

};

#endif // !INFINITEAREALIGHT_H_

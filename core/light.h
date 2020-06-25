/*
 * light.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "../common/math.h"

///////////////////////////////////////////////////////////////////////////
// Light                                                                 //
///////////////////////////////////////////////////////////////////////////

class Light {

public:
    Light() = default;
     
    ~Light() = default;
    
    virtual glm::vec3 sampleLight(glm::vec3 dest) = 0;

protected:

};


#endif // !LIGHT_H_

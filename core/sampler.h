/*
 * sampler.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef SAMPLER_H_
#define SAMPLER_H_

#include "../common/glm_common.h"

 ///////////////////////////////////////////////////////////////////////////
 // Sampler                                                               //
 ///////////////////////////////////////////////////////////////////////////

class Sampler
{
public:
    Sampler(int samplesPerPixel);

    virtual ~Sampler() = default;

protected:
    const int m_samplesPerPixel;
};

#endif // !DISNEY_H_

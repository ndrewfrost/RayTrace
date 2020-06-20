/*
 * halton.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef HALTON_H_
#define HALTON_H_

#include "../core/sampler.h"

///////////////////////////////////////////////////////////////////////////
// Halton Sampler                                                        //
///////////////////////////////////////////////////////////////////////////

class HaltonSampler : public Sampler
{
    HaltonSampler(int numberSamples);
};

#endif // !HALTON_H_

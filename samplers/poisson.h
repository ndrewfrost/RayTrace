/*
 * poisson.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef POISSON_H_
#define POISSON_H_

#include "../core/sampler.h"

///////////////////////////////////////////////////////////////////////////
// Poisson Sampler                                                       //
///////////////////////////////////////////////////////////////////////////

class PoissonSampler : public Sampler
{
    PoissonSampler(int numberSamples);
};

#endif // !POISSON_H_
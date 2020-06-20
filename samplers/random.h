/*
 * random.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include "../core/sampler.h"

///////////////////////////////////////////////////////////////////////////
// Random Sampler                                                        //
///////////////////////////////////////////////////////////////////////////

class RandomSampler : public Sampler
{
    RandomSampler(int numberSamples);
};

#endif // !RANDOM_H_

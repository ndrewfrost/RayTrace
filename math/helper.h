#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <cmath>

namespace helper {
    inline float deg2rad (double degrees) {
        static const double pi_on_180 = 4.0 * atan (1.0) / 180.0;
        return degrees * pi_on_180;
    }
}

#endif
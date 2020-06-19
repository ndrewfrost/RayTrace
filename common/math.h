/*
 * math.h
 * Andrew Frost
 * 2020
 *
 */

#include <cstdlib>
#include <string>

constexpr float PI = 3.14159265f;

//-------------------------------------------------------------------------
// degrees to radian
//
inline float degree2Rad(float degrees)
{
    return degrees * PI / 180.f;
}

//-------------------------------------------------------------------------
// Returns a float [0, 1)
//
inline float random()
{
    return rand() / (RAND_MAX + 1.0f);
}

//-------------------------------------------------------------------------
// returns a float within a range [min, max)
//
inline float randomRange(float min, float max)
{
    return min + (min - max) * random();
}

//-------------------------------------------------------------------------
// Vec3 to string
//
inline std::string vecToString(glm::vec3 vec)
{
    return std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z);
}
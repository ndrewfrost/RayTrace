/*
 * math.h
 * Andrew Frost
 * 2020
 *
 */

#ifndef MATH_HELP_H_
#define MATH_HELP_H_

#include "glm_common.h"
#include <random>
#include <string>

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float PI = 3.14159265f;

//-------------------------------------------------------------------------
// square funtion
//
inline float sqr(float x)
{
    return x * x;
}

//-------------------------------------------------------------------------
// clamp within range (min, max)
//
inline float clamp(float x, float min, float max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
//-------------------------------------------------------------------------
// degrees to radian
//
inline float degree2Rad(float degrees)
{
    return (degrees * PI / 180.f);
}

//-------------------------------------------------------------------------
// Returns a float [0, 1)
//
inline float randomFloat()
{
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

//-------------------------------------------------------------------------
// returns int [min,max]
//
inline int randomInt(int min, int max)
{
    std::random_device rdevice; 
    std::mt19937 generator(rdevice());
    std::uniform_int_distribution<> distribution(min, max);

    return distribution(generator);
}

//-------------------------------------------------------------------------
// returns a float within a range [min, max)
//
inline float randomFloat(float min, float max)
{
    return min + (max-min) * randomFloat();
}

//-------------------------------------------------------------------------
// Returns a vec3 with scalars between [0,1)
//
inline glm::vec3 randomVec3()
{
    return glm::vec3(randomFloat(), randomFloat(), randomFloat());
}

//-------------------------------------------------------------------------
// Returns a vec3 with scalars between [min,max)
//
inline glm::vec3 randomVec3(float min, float max)
{
    return glm::vec3(randomFloat(min, max), 
                     randomFloat(min, max), 
                     randomFloat(min, max));
}

//-------------------------------------------------------------------------
// Generate a point in a unit sphere (A rejection method
//
inline glm::vec3 rndPointUnitSphere()
{
    while (true) {
        glm::vec3 point = randomVec3(-1.0f, 1.f);
        if (glm::dot(point, point) >= 1) continue;
        return point;
    }
}

//-------------------------------------------------------------------------
// Generate a point in a unit disk (A rejection method)
//
inline glm::vec2 rndPointUnitDisk()
{
    while (true) {
        glm::vec2 point(randomFloat(), randomFloat());
        if (glm::dot(point, point) >= 1) continue;
        return point;
    }
}

//-------------------------------------------------------------------------
// Rotate around axis, X then Y then Z
//
inline glm::vec3 rotate(glm::vec3 point, glm::vec3 rotation) {
    return glm::rotateZ(glm::rotateY(glm::rotateX(point, glm::radians(rotation.x)), glm::radians(rotation.y)), glm::radians(rotation.z));
}

//-------------------------------------------------------------------------
// Vec3 to string
//
inline std::string vecToString(glm::vec3 vec)
{
    return std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z);
}



#endif // !MATH_HELP_H_
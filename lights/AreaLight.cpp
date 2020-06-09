/*
 * AreaLight.cpp
 *
 *
 */
#include "AreaLight.h"



namespace rt {


    /*Vec3f AreaLight::randomDirection(Vec3f direction, float spread) {
        const double PI = 3.141592653589793;

        //create a base 

        Vec3f  v3 = direction;
        v3.normalize();

        Vec3f different = (fabs(v3.x) < 0.5f) ? Vec3f(1.0f, 0.0f, 0.0f) : Vec3f(0.0f, 1.0f, 0.0f);
        Vec3f v1 = v3.crossProduct(different);
        v1.normalize();
        Vec3f v2 = v1.crossProduct(v3);

        // Pick (x,y,z) randomly around (0,0,1)
        float z = randomMath::random(std::cos(spread * PI), 1);
        float r = sqrtf(1.0f - z * z);
        float theta = randomMath::random(-PI, PI);
        float x = r * cos(theta);
        float y = r * sin(theta);

        // return hemsipher vector
        return x * v1 + y * v2 + z * v3;
    }*/



} //namespace rt

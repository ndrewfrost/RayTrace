/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"

namespace rt {

    /*
     * Ray structure definition
     */
    enum RayType { PRIMARY, SECONDARY, SHADOW };

    struct Ray{
	    RayType raytype;
    
        Vec3f origin;
        Vec3f direction;
    };


    struct Hit {
        bool hit = false;
        float distance;

        Vec3f surfaceNormal;
        Vec3f viewDirection;

        Vec3f hitPoint;
        Vec3f color;
        uint32_t shape;

        bool textureBool = false;
        Vec3f* texture;

        bool areaLight = false;

        bool backSurface = false;
    };

}


#endif /* CORE_RAYHITSTRUCTS_H_ */

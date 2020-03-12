/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt {

    Camera::~Camera() {};

    void Camera::lookMatrix() {

        Vec3f dir = (location - lookAt).normalize();

        //Vec3f(0,1,0) is up vector
        Vec3f right = (Vec3f(0, 1, 0).crossProduct(dir)).normalize();

        Vec3f up = dir.crossProduct(right);

        cameraToWorld[3][0] = location.x;
        cameraToWorld[3][1] = location.y;
        cameraToWorld[3][2] = location.z;
        cameraToWorld[3][3] = 1;

        cameraToWorld[0][0] = right.x;
        cameraToWorld[0][1] = right.y;
        cameraToWorld[0][2] = right.z;

        cameraToWorld[1][0] = up.x;
        cameraToWorld[1][1] = up.y;
        cameraToWorld[1][2] = up.z;

        cameraToWorld[2][0] = dir.x;
        cameraToWorld[2][1] = dir.y;
        cameraToWorld[2][2] = dir.z;

        cameraToWorld[0][3] = 0;
        cameraToWorld[1][3] = 0;
        cameraToWorld[2][3] = 0;

        //cameraToWorld.inverse();
    };


    /**
     * Factory function that returns camera subclass based on camera specifications
     *
     * @param cameraSpecs camera specifications json object
     *
     * @return camera subclass instance
     *
     */
    Camera* Camera::createCamera(Value& cameraSpecs) {

        //check if cameratype is defined

        if (!cameraSpecs.HasMember("type")) {
            std::cerr << "Camera type not specified" << std::endl;
            exit(-1);
        }

        std::string cameraType = cameraSpecs["type"].GetString();

        //return camera object based on camera specs
        if (cameraType.compare("pinhole") == 0) {
            return new Pinhole(cameraSpecs["width"].GetInt(),
                cameraSpecs["height"].GetInt(),
                cameraSpecs["fov"].GetInt(),
                Vec3f(cameraSpecs["location"][0].GetFloat(), cameraSpecs["location"][1].GetFloat(), cameraSpecs["location"][2].GetFloat()),
                Vec3f(cameraSpecs["look"][0].GetFloat(), cameraSpecs["look"][1].GetFloat(), cameraSpecs["look"][2].GetFloat()));

        }
        else if (cameraType.compare("thinlens") == 0) {
            ThinLens* thin = new ThinLens(cameraSpecs["width"].GetInt(),
                cameraSpecs["height"].GetInt(),
                cameraSpecs["fov"].GetInt(),
                Vec3f(cameraSpecs["location"][0].GetFloat(), cameraSpecs["location"][1].GetFloat(), cameraSpecs["location"][2].GetFloat()),
                Vec3f(cameraSpecs["look"][0].GetFloat(), cameraSpecs["look"][1].GetFloat(), cameraSpecs["look"][2].GetFloat()),
                cameraSpecs["aperture"].GetFloat(),
                cameraSpecs["focal"].GetFloat());

            int x = 1;
            int y = 1;
            if (cameraSpecs.HasMember("sampling")) {
                thin->setSampling(cameraSpecs["sampling"].GetString());
                if (cameraSpecs.HasMember("nsamplesx")) {
                    x = cameraSpecs["nsamplesx"].GetInt();
                }
                if (cameraSpecs.HasMember("nsamplesy")) {
                    y = cameraSpecs["nsamplesy"].GetInt();
                }
                thin->setNumSamples(Vec2i(x, y));
                std::cout << "Samples : " << x * y << std::endl;
            }
            std::cout << "Sampling : " << thin->getSampling() << std::endl;
            return thin;
        }

        return 0;

    }



} //namespace rt

/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "math/geometry.h"


using namespace rapidjson;

namespace rt {

    class Camera {
    public:

        //
        // Constructors
        //
        Camera(int width, int height, int fov) :height(height), width(width), fov(fov) {};
        Camera(int width, int height, int fov, Vec3f location, Vec3f lookAt) :height(height), width(width), fov(fov), location(location), lookAt(lookAt) {};

        //
        // Destructor
        //
        virtual ~Camera();

        //
        // factory function : returns camera instance dynamically based on camera specifications
        //
        static Camera* createCamera(Value& cameraSpecs);


        //
        // print function (to be implemented by the subclasses )
        //
        virtual void printCamera() = 0;

        // Sets the camera To World Matrix
        void lookMatrix();

        // Ray origin and Direction
        virtual void getOriginDirection(float& pixelX, float& pixelY, Vec3f& origin, Vec3f& direction, Vec2i& sample, Vec2i& samplingSize) = 0;

        //
        // Getters and Setters
        //
        int getHeight() const {
            return height;
        }

        void setHeight(int height) {
            this->height = height;
        }

        int getWidth() const {
            return width;
        }

        void setWidth(int width) {
            this->width = width;
        }

        float getFOV() const {
            return fov;
        }

        Matrix44f getCameraToWorld() {
            return cameraToWorld;
        }

        virtual Vec3f getLocation() {
            return location;
        }

        Vec3f getLookAt() {
            return lookAt;
        }


        Vec2i getNumSamples() {
            return nsamples;
        }

        void setNumSamples(Vec2i n) {
            nsamples = n;
        }

        std::string getSampling() {
            return sampling;
        }

        void setSampling(std::string s) {
            sampling = s;
        }

    protected:

        std::string sampling = "none";
        Vec2i nsamples = Vec2i(1, 1);

        //
        //camera members
        //
        int height;
        int width;
        int fov; //field of view

        //Location of camera
        Vec3f location;
        //Location camera is looking at
        Vec3f lookAt;

        //Matrix for camera to world transformation
        Matrix44f cameraToWorld;

    };

} //namespace rt



#endif /* CAMERA_H_ */

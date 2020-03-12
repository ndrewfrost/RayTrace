/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"

namespace rt {

    // Convert deg to radian
    inline float deg2rad(double degrees) {
        static const double pi_on_180 = 4.0 * atan(1.0) / 180.0;
        return degrees * pi_on_180;
    }

    /**
     * Performs ray tracing to render a photorealistic scene
     *
     * @param camera the camera viewing the scene
     * @param scene the scene to render, including objects and lightsources
     * @param nbounces the number of bounces to consider for raytracing
     *
     * @return a pixel buffer containing pixel values in linear RGB format
     */
    Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces, std::string sampling, Vec2i nsamples) {
        Vec3f* pixelbuffer = new Vec3f[camera->getWidth() * camera->getHeight()];
        Vec3f* output = pixelbuffer;

        float imageAspectRatio;
        if (camera->getWidth() > camera->getHeight()) {
            imageAspectRatio = camera->getWidth() / camera->getHeight();
        }
        else {
            imageAspectRatio = camera->getHeight() / camera->getWidth();
        }

        float scale = tan(rt::deg2rad(camera->getFOV() * 0.5));

        for (int vert = 0; vert < camera->getHeight(); ++vert) {
            for (int hor = 0; hor < camera->getWidth(); ++hor) {
                // Random Sampling
                if (sampling == "random") {
                    Vec2i samplingPos(-1, -1);
                    Vec2i samplingSize;
                    Vec3f color;

                    for (int sample = 0; sample < nsamples.x * nsamples.y; sample++) {
                        float pixelX = (2 * (hor + 0.5) / camera->getWidth() - 1) * scale;
                        float pixelY = (1 - 2 * ((vert + 0.5) / camera->getHeight())) * scale;
                        if (camera->getWidth() > camera->getHeight()) {
                            pixelX *= imageAspectRatio;
                        }
                        else {
                            pixelY *= imageAspectRatio;
                        }

                        Vec3f origin, direction;
                        camera->getOriginDirection(pixelX, pixelY, origin, direction, samplingPos, samplingSize);
                        color = color + castRay(origin, direction, scene->getShapes(), scene->getLightSources(), scene->getBackgroundColor(), PRIMARY, nbounces);
                    }
                    color.x = color.x / (nsamples.x * nsamples.y);
                    color.y = color.y / (nsamples.x * nsamples.y);
                    color.z = color.z / (nsamples.x * nsamples.y);
                    *(pixelbuffer++) = color;

                }
                // Jittered
                else if (sampling == "jittered") {
                    Vec2i samplingPos(-1, -1);
                    Vec2i samplingSize(nsamples.x, nsamples.y);
                    Vec3f color;
                    for (int samplex = 0; samplex < nsamples.x; samplex++) {
                        for (int sampley = 0; sampley < nsamples.y; sampley++) {
                            float pixelX = (2 * (hor + 0.5) / camera->getWidth() - 1) * scale;
                            float pixelY = (1 - 2 * ((vert + 0.5) / camera->getHeight())) * scale;
                            if (camera->getWidth() > camera->getHeight()) {
                                pixelX *= imageAspectRatio;
                            }
                            else {
                                pixelY *= imageAspectRatio;
                            }

                            Vec3f origin, direction;
                            samplingPos = Vec2i(samplex, sampley);
                            camera->getOriginDirection(pixelX, pixelY, origin, direction, samplingPos, samplingSize);
                            color = color + castRay(origin, direction, scene->getShapes(), scene->getLightSources(), scene->getBackgroundColor(), PRIMARY, nbounces);
                        }
                    }
                    color.x = color.x / (nsamples.x * nsamples.y);
                    color.y = color.y / (nsamples.x * nsamples.y);
                    color.z = color.z / (nsamples.x * nsamples.y);
                    *(pixelbuffer++) = color;

                }
                // no sampling/pinhole
                else {
                    Vec2i sampling(-1, -1);
                    Vec2i samplingSize;
                    float pixelX = (2 * (hor + 0.5) / camera->getWidth() - 1) * scale;
                    float pixelY = (1 - 2 * ((vert + 0.5) / camera->getHeight())) * scale;

                    if (camera->getWidth() > camera->getHeight()) {
                        pixelX *= imageAspectRatio;
                    }
                    else {
                        pixelY *= imageAspectRatio;
                    }


                    Vec3f origin, direction;
                    camera->getOriginDirection(pixelX, pixelY, origin, direction, sampling, samplingSize);
                    *(pixelbuffer++) = castRay(origin, direction, scene->getShapes(), scene->getLightSources(), scene->getBackgroundColor(), PRIMARY, nbounces);
                }
            }
        }

        return output;

    }

    Hit RayTracer::traceRay(Ray& ray,
        std::vector<Shape*>& shapes,
        std::vector<LightSource*>& lights,
        int light) {

        Hit* hits = new Hit[shapes.size()];
        Hit* areaHits = new Hit[lights.size()];
        Hit* areaHit = areaHits;
        Hit* hit = hits;
        Hit closest;

        // Test for shadows/Light
        if (ray.raytype == SHADOW) {
            float lightDistance = fabs(ray.direction.length());
            for (int s = 0; s < shapes.size(); s++) {
                *hit = shapes[s]->intersect(ray);
                if (hit->hit) {
                    if (closest.hit) {
                        if (lightDistance < hit->distance) {
                            closest.hit = true;
                        }
                    }
                    else {
                        closest = *hit;
                    }
                }
                hit++;
            }
        }
        //Primary && Secondary Ray intersection
        else {
            for (int s = 0; s < shapes.size(); s++) {
                *hit = shapes[s]->intersect(ray);
                hit->shape = s;
                if (hit->hit) {
                    if (closest.hit) {
                        if (closest.distance <= hit->distance) {
                            closest = *hit;
                        }
                    }
                    else {
                        closest = *hit;
                    }
                }
                hit++;
            }

            //Does ray hit Area Light
            for (int l = 0; l < lights.size(); l++) {
                if (lights[l]->isAreaLight()) {
                    Shape* area = lights[l]->getAreaLight();
                    *areaHit = area->intersect(ray);
                    areaHit->shape = l;
                    areaHit->areaLight = true;
                    if (areaHit->hit) {
                        if (closest.hit) {
                            if (closest.distance <= areaHit->distance) {
                                closest = *areaHit;
                            }
                        }
                        else {
                            closest = *areaHit;
                        }
                    }
                }
                areaHit++;
            }

        }
        delete[] hits;
        delete[] areaHits;
        return closest;
    }

    Vec3f RayTracer::castRay(Vec3f& origin, Vec3f& direction,
        std::vector<Shape*>& shapes,
        std::vector<LightSource*>& lights,
        Vec3f& backgroundColor,
        RayType rayType,
        int nbounces) {

        Vec3f hitColor(0, 0, 0);

        if (nbounces == 0) return hitColor;
        if (rayType == PRIMARY) hitColor = backgroundColor;

        Ray ray;
        ray.raytype = rayType;
        ray.origin = origin;
        ray.direction = direction;

        //Cast to Every Object return closest object if ray hits object
        Hit closest = traceRay(ray, shapes, lights, 0);

        if (!(closest.hit)) return hitColor;
        if (closest.areaLight) {
            return (lights[closest.shape]->getColor());
        }
        hitColor = Vec3f();


        BlinnPhong material = shapes[closest.shape]->getMaterial();
        Vec3f blinn;

        // Calculate BlinnPhong for all lights
        for (int l = 0; l < lights.size(); l++) {
            for (int sx = 0; sx < lights[l]->getSamples(); sx++) {
                for (int sy = 0; sy < lights[l]->getSamples(); sy++) {

                    Ray shadow;
                    shadow.raytype = SHADOW;

                    // move shadow origin slightly above or below surface
                    if (closest.backSurface) {
                        shadow.origin = (closest.hitPoint) - (0.001f * closest.surfaceNormal);
                    }
                    else {
                        shadow.origin = (closest.hitPoint) + (0.001f * closest.surfaceNormal);
                    }

                    Vec3f randomPoint;
                    if (lights[l]->isAreaLight()) {
                        if (lights[l]->getSampling() == "random") {
                            randomPoint = lights[l]->getAreaLight()->getRandomPosition();
                            shadow.direction = -shadow.origin + randomPoint;
                            sy = lights[l]->getSamples();
                        }
                        else if (lights[l]->getSampling() == "jittered") {
                            Vec2i sampling(lights[l]->getSamples(), lights[l]->getSamples());
                            Vec2i sample(sx, sy);
                            randomPoint = lights[l]->getAreaLight()->getJitteredPosition(sampling, sample);
                            shadow.direction = -shadow.origin + randomPoint;
                        }

                    }
                    else {
                        sx = lights[l]->getSamples(); // no extra sampling for point lights
                        sy = lights[l]->getSamples();
                        shadow.direction = -shadow.origin + lights[l]->getPosition();
                    }

                    float distance = fabs(shadow.direction.length());
                    shadow.direction.x /= distance;
                    shadow.direction.y /= distance;
                    shadow.direction.z /= distance;

                    // Check if Shadow Ray
                    Hit light = traceRay(shadow, shapes, lights, l);

                    // Blinn Phong material 
                    if (shapes[closest.shape]->hasTexture()) {
                        Vec3f texture = shapes[closest.shape]->getColor(closest.hitPoint);
                        antiTonemap(texture);
                        blinn = blinn + material.getAmbient(texture);
                    }
                    else {
                        blinn = blinn + material.getAmbient();
                    }
                    if (light.hit != true) {

                        // Vectors for material
                        Vec3f halfAngle, lightDirection;
                        if (lights[l]->isAreaLight()) {
                            lightDirection = -(closest.hitPoint - randomPoint);
                        }
                        else {
                            lightDirection = -(closest.hitPoint - lights[l]->getPosition());
                        }
                        lightDirection.normalize();
                        halfAngle = lightDirection + closest.viewDirection;
                        halfAngle.normalize();

                        // Texture or Not
                        if (shapes[closest.shape]->hasTexture()) {
                            Vec3f texture = shapes[closest.shape]->getColor(closest.hitPoint);
                            antiTonemap(texture);
                            blinn = blinn + material.getDiffuse(lightDirection, closest.surfaceNormal, texture, lights[l]->getColor(), lights[l]->getIntensity(), distance);
                        }
                        else {
                            blinn = blinn + material.getDiffuse(lightDirection, closest.surfaceNormal, lights[l]->getColor(), lights[l]->getIntensity(), distance);
                        }
                        blinn = blinn + material.getSpecular(halfAngle, closest.surfaceNormal, lights[l]->getColor(), lights[l]->getIntensity(), distance);
                    }
                }
            }
            float div;
            if (lights[l]->getSampling() == "jittered") {
                div = lights[l]->getSamples() * lights[l]->getSamples();
            }
            else {
                div = lights[l]->getSamples();
            }
            blinn.x = blinn.x / div;
            blinn.z = blinn.z / div;
            blinn.y = blinn.y / div;

            hitColor = hitColor + blinn;
        }

        // Cast Secondary Rays


        ray.origin = (closest.hitPoint) + (0.001f * closest.surfaceNormal);
        ray.direction = (closest.viewDirection * -1) - 2 * (closest.viewDirection * -1).dotProduct(closest.surfaceNormal) * closest.surfaceNormal;

        float distance = sqrtf(ray.direction.norm());
        ray.direction.x /= distance;
        ray.direction.y /= distance;
        ray.direction.z /= distance;


        Vec3f reflectionColor;
        nbounces--;
        for (int s = 0; s < shapes.size(); s++) {
            reflectionColor = castRay(ray.origin, ray.direction, shapes, lights, backgroundColor, SECONDARY, nbounces);
            hitColor = hitColor + (material.getReflective() * reflectionColor);
        }


        return hitColor;
    }


    /**
     * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
     *
     * @param pixelbuffer the array of size width*height containing linear RGB pixel values
     *
     * @return the tonemapped image
     */
    Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer, uint32_t width, uint32_t height) {
        for (int i = 0; i < height * width; i++) {
            pixelbuffer[i].x = (pixelbuffer[i].x >= 1.0 ? 255 : (pixelbuffer[i].x <= 0.0 ? 0 : (int)floor(pixelbuffer[i].x * 256.0)));
            pixelbuffer[i].y = (pixelbuffer[i].y >= 1.0 ? 255 : (pixelbuffer[i].y <= 0.0 ? 0 : (int)floor(pixelbuffer[i].y * 256.0)));
            pixelbuffer[i].z = (pixelbuffer[i].z >= 1.0 ? 255 : (pixelbuffer[i].z <= 0.0 ? 0 : (int)floor(pixelbuffer[i].z * 256.0)));
        }
        return pixelbuffer;
    }

    //
    void RayTracer::antiTonemap(Vec3f& pixelbuffer) {
        pixelbuffer.x = (pixelbuffer.x >= 255 ? 1.0 : (pixelbuffer.x <= 0.0 ? 0.0 : (pixelbuffer.x / 256.0)));
        pixelbuffer.y = (pixelbuffer.y >= 255 ? 1.0 : (pixelbuffer.y <= 0.0 ? 0.0 : (pixelbuffer.y / 256.0)));
        pixelbuffer.z = (pixelbuffer.z >= 255 ? 1.0 : (pixelbuffer.z <= 0.0 ? 0.0 : (pixelbuffer.z / 256.0)));
    }



} //namespace rt



/*
 * main.cpp
 *
 */

#include <iostream>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "math/geometry.h"
#include "parsers/PPMWriter.h"

#include "core/RayTracer.h"
#include "core/Camera.h"
#include "core/Scene.h"


using namespace rt;
using namespace rapidjson;

int main(int argc, char* argv[]) {

    //parse commandline arguments
    //char* inputFile = "../examples/test.json";    //first command line argument holds the path to the json input file
    //char* outputFile = "C:/Users/Andrew.DESKTOP-P89GBJ7/Desktop/out.ppm";   //second command line argument holds the path to the output image file

    char* inputFile = argv[1];
    char* outputFile = argv[2];

    std::printf("Input file: %s\n", inputFile);

    //parse json input file using rapidjson
    std::ifstream ifs(inputFile);
    IStreamWrapper is(ifs);
    Document d;     // d holds the complete json object
    d.ParseStream(is);

    //generate a camera according to the input file
    Camera* camera = Camera::createCamera(d["camera"]);
    uint32_t width = camera->getWidth();
    uint32_t height = camera->getHeight();
    //print camera data (based on the input file provided)
    camera->printCamera();

    //generate the scene according to the input file
    Scene* scene = new Scene();
    scene->createScene(d["scene"]);
    std::cout << "Scene Loaded" << std::endl;

    //
    // Main function, render scene
    //

    Vec3f* pixelbuffermain = RayTracer::render(camera, scene, d["nbounces"].GetInt(), camera->getSampling(), camera->getNumSamples());
    RayTracer::tonemap(pixelbuffermain, width, height);


    // 
    // The loop below was used for MSE of sampling
    //

    /*for (int sampling = 1; sampling <= 45; sampling++) {
        std::cout << camera->getNumSamples() << std::endl;
        Vec3f* pixelbuffer = RayTracer::render(camera, scene, d["nbounces"].GetInt(), "random", Vec2i(sampling, sampling));

        //convert linear RGB pixel values [0-1] to range 0-255
        RayTracer::tonemap(pixelbuffer, width, height);
        float accuracy = 0;
        for (int s = 0; s < camera->getWidth() * camera->getHeight(); s++) {
            //std::cout << pixelbuffermain[s].x << pixelbuffer[s].x << std::endl;
            float x = pixelbuffermain[s].x - pixelbuffer[s].x;
            float y = pixelbuffermain[s].y - pixelbuffer[s].y;
            float z = pixelbuffermain[s].z - pixelbuffer[s].z;
            accuracy = accuracy + pow(x, 2) + pow(y, 2) + pow(z, 2);
        }

        std::ofstream myfile;
        myfile.open("C:/Users/Andrew.DESKTOP-P89GBJ7/Desktop/randomthin.txt", std::ios_base::app);
        myfile << sampling << "," << accuracy << "\n";
        myfile.close();

        delete pixelbuffer;
    }*/

    //free resources when rendering is finished
    
    delete scene;
    delete camera;

    //write rendered scene to file (pixels RGB values must be in range 0-255)
    PPMWriter::PPMWriter(width, height, pixelbuffermain, outputFile);

    delete pixelbuffermain;


}



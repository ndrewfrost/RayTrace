// Andrew Frost

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <utility> 

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "../core/camera.h"
#include "../core/raytracer.h"
#include "../core/scene.h"

using std::unique_ptr;

//------------------------------------------------------------------------------------
// 
//
static void display(GLFWwindow* window) {
    glClearColor(0.5, 0, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

//-------------------------------------------------------------------------
// GLFW on Error Callback
//
static void onErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

//------------------------------------------------------------------------------------
// glfw Keyboard Callback
//
static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        return;
    }
    switch (key) {
    case GLFW_KEY_SPACE:
        break;
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, 1);
        break;
    case GLFW_KEY_Q:
        glfwSetWindowShouldClose(window, 1);
        break;
    }
}

//------------------------------------------------------------------------------------
// Main / Entry Point
//
int main(int argc, char** argv) {

    // Parse input arguments
    char* inputFile = argv[1];

    // Input file check
    if ((inputFile == NULL) || (inputFile[0] == '\0')) {
        std::cerr << "ERROR: No input file" << std::endl;
        return 0;
    }

    // Parse input file
    std::ifstream ifs(inputFile);
    rapidjson::IStreamWrapper is(ifs);
    rapidjson::Document doc;
    doc.ParseStream(is);

    // generate a camera
    unique_ptr<Camera> camera;

    // generate the scene
    unique_ptr<Scene> scene;

    // render scene 
    RayTracer tracer;

    // GUI
    glfwSetErrorCallback(onErrorCallback);
    if (!glfwInit()) return;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(500, 500, "Title", NULL, NULL);

    glfwSetKeyCallback(window, keyboard);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
    

    // Main Display Loop
    while (!glfwWindowShouldClose(window)) {

        display(window);
              
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

/*

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "math/geometry.h"
#include "parsers/PPMWriter.h"

#include "core/RayTracer.h"
#include "core/Camera.h"
#include "core/Scene.h"

using namespace rt;

int main(int argc, char* argv[]) {

    char* outputFile = argv[2];

    // Output file check
    if ((outputFile == NULL) || (outputFile[0] == '\0')) {
        outputFile = "output.ppm";
    }


    // Parse input file
    std::ifstream ifs(inputFile);
    IStreamWrapper is(ifs);
    Document d;
    d.ParseStream(is);

    // generate a camera
    std::unique_ptr<Camera> camera = Camera::createCamera(d["camera"]);
    camera->printCamera();

    // generate the scene
    std::unique_ptr<Scene> scene = new Scene();
    scene->createScene(d["scene"]);

    // render scene
    std::unique_ptr<Vec3f> pixelbuffermain = RayTracer::render(camera, scene);

    std::printf("Output file : %s\n", outputFile);

    // Write rendered scene to file
    PPMWriter::PPMWriter();*/
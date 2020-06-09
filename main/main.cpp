// Andrew Frost

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "../core/camera.h"
#include "../core/raytracer.h"
#include "../core/scene.h"

void display(GLFWwindow* window) {
    glClearColor(0.5, 0, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
    Camera* camera = Camera::createCamera(doc["camera"]);

    // generate the scene
    Scene* scene = new Scene();
    scene->createScene(doc["scene"]);

    // render scene 
    RayTracer tracer = RayTracer(camera, scene);

    // GUI
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(500, 500, "Title", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, keyboard);

    // Main Display Loop
    while (!glfwWindowShouldClose(window)) {

        display(window);

        if (!tracer.finisedRender()) {
        }
      
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    delete scene;
    delete camera;

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
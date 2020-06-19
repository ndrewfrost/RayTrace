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
#include "../parsers/parser.h"

using std::unique_ptr;

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------
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


///////////////////////////////////////////////////////////////////////////
// Main / Entry Point                                                    //
///////////////////////////////////////////////////////////////////////////

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
    assert(doc.HasMember("camera") && "Input Json must have member camera");
    unique_ptr<Camera> camera = Parser::readCamera(doc["camera"]);

    // generate the scene
    unique_ptr<Scene> scene = Parser::readScene(doc["scene"]);

    // render scene 
    //RayTracer tracer;

    // GUI
    glfwSetErrorCallback(onErrorCallback);
    if (!glfwInit()) return EXIT_FAILURE;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(500, 500, "RayTracing", NULL, NULL);

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

    return EXIT_SUCCESS;
}
// Andrew Frost

#include <SDL.h>

#include <iostream>
#include <fstream>
#include <utility> 

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "../core/camera.h"
#include "../core/raytracer.h"
#include "../core/scene.h"
#include "../io/parser.h"
#include "../io/display.h"

using std::unique_ptr;

const unsigned int g_width = 500;
const unsigned int g_height = 500;

///////////////////////////////////////////////////////////////////////////
// Main / Entry Point                                                    //
///////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

    // Parse input arguments
    char* inputFile = argv[1];

    // Input file check
    if ((inputFile == NULL) || (inputFile[0] == '\0')) {
        std::cerr << "ERROR: No input file" << std::endl;
        return EXIT_FAILURE;
    }

    // Parse input file
    std::ifstream ifs(inputFile);
    if (!ifs) {
        std::cout << "[" << inputFile << "] file cannot be found" << std::endl;
        return EXIT_FAILURE;
    }

    rapidjson::IStreamWrapper is(ifs);
    rapidjson::Document doc;
    doc.ParseStream(is);
    ifs.close();

    // generate a camera
    assert(doc.HasMember("camera") && "Input Json must have member camera");
    unique_ptr<Camera> camera = Parser::readCamera(doc["camera"]);

    // generate the scene
    unique_ptr<Scene> scene = Parser::readScene(doc["scene"]);

    // render scene 
    //RayTracer tracer;

    // GUI
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Ray Tracing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        g_width, g_height,
        SDL_WINDOW_SHOWN);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    uint32_t* buffer = static_cast<uint32_t*>(surface->pixels);

    bool exit = false;

    SDL_LockSurface(surface);

    // Write color values to pixels here.
    // Example of making row 10 column 20 a white pixel
    buffer[10 * g_width + 20] = 0xFFFFFFFF;

    SDL_UnlockSurface(surface);
    SDL_UpdateWindowSurface(window);

    // Wait for window exit
    while (!exit)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                exit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
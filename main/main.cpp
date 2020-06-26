// Andrew Frost

#include <SDL.h>

#include <iostream>
#include <fstream>
#include <utility> 
#include <chrono>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "../core/camera.h"
#include "../core/raytracer.h"
#include "../core/scene.h"
#include "../io/parser.h"
#include "../io/display.h"

using std::shared_ptr;

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

    // Read renderer settings
    assert(doc.HasMember("settings") && "Input Json must have member settings");
    shared_ptr<Settings> settings = Parser::readSettings(doc["settings"]);

    // generate a camera
    assert(doc.HasMember("camera") && "Input Json must have member camera");
    shared_ptr<Camera> camera = Parser::readCamera(doc["camera"], settings);

    // generate the scene
    shared_ptr<Scene> scene = Parser::readScene(doc["scene"], settings);
   
    // generate output
    shared_ptr<DisplayImage> output = std::make_shared<DisplayImage>(settings);

    // render scene 
    RayTracer tracer = RayTracer(camera, scene, output);
    auto t1 = std::chrono::high_resolution_clock::now();

    tracer.render();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

    std::cout << "\nTime to Render: " <<  duration << "ms" << std::endl;

    // GUI
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Ray Tracing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        settings->width, settings->height,
        SDL_WINDOW_SHOWN);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    uint32_t* buffer = static_cast<uint32_t*>(surface->pixels);

    bool exit = false;

    SDL_LockSurface(surface);

    // Write color values to pixels
    output->fillBuffer(buffer);

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
///Created by Daniel Amador dos Santos
///Based on Shader Project example provided by Ole Marius Kohmann

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GL_Controller.h"

class SDL_Controller
{
    int screenWidth;
    int screenHeight;
    Uint32 flags;
    SDL_Event event;
    bool quit;

public:
    SDL_Window* window;
    SDL_GLContext glContext;

    void CreateWindandContext(int w, int h, Uint32 flgs);
    bool processEvents();
    void renderLoop(GL_Controller *glControl);

    SDL_Controller();
    ~SDL_Controller();
};

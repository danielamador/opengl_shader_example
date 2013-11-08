///Created by Daniel Amador dos Santos
///Based on Shader Project example provided by Ole Marius Kohmann
#include "SDL_Controller.h"

SDL_Controller::SDL_Controller()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        std::cout<<"SDL2 couldn't init.\nError: "<< SDL_GetError()
                 <<std::endl;
    }

    quit = false;
}

SDL_Controller::~SDL_Controller()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL_Controller::CreateWindandContext(int w, int h, Uint32 flgs)
{
    screenWidth  = w;
    screenHeight = h;
    flags        = flgs;

    window    = SDL_CreateWindow("First SDL2 OGL App", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, flags);
    glContext = SDL_GL_CreateContext(window);

    if (window == NULL)
        std::cout<<"Error creating window!"<<std::endl;
    if (glContext == NULL)
    {
        std::cout<<"Error creating GL Context!\nError: "<< SDL_GetError()
                 <<std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

bool SDL_Controller::processEvents()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_q:
        {
            quit = true;
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return quit;
}

void SDL_Controller::renderLoop(GL_Controller *glControl)
{
    int timer = SDL_GetTicks();
    while(processEvents()==false)
    {
        glControl->rotateModel();
        glControl->drawCube();
        SDL_GL_SwapWindow(window);
        SDL_Delay((1000/30) - (timer-SDL_GetTicks()));
        timer = SDL_GetTicks();
    }

}


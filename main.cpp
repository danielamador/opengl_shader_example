///Created by Daniel Amador dos Santos
///Based on Shader Project example provided by Ole Marius Kohmann
#include<iostream>
#include "GL_Controller.h"
#include "SDL_Controller.h"

int main(int argc, char *argv[])
{
    int width = 800;
    int height = 600;
    //std::cout<<"Hello World!\n";
    GL_Controller *glControl;
    SDL_Controller *sdlControl;

    sdlControl = new SDL_Controller();
    sdlControl->CreateWindandContext(width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    //You have to initialize SDL before OpenGL for GLEW not complain about Missing GL Version
    glControl = new GL_Controller(width, height);
    glControl->loadShaders("min.vert", "min.frag");

    sdlControl->renderLoop(glControl);



    return 0;
}

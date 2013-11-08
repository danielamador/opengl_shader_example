///Created by Daniel Amador dos Santos
///Based on Shader Project example provided by Ole Marius Kohmann
#include <iostream>
#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#ifndef GL_CONTROLLER_H
#define GL_CONTROLLER_H

class GL_Controller
{
    GLfloat rotation;

public:
    void drawCube();
    void rotateModel();
    void loadShaders(const char* vertshadefile, const char* fragshadefile);
    GL_Controller(int w, int h);

    class Shader
    {
        GLhandleARB vertexShader,
                    fragmentShader,
                    shaderProgram;

        void printInfoLog(GLhandleARB obj);
        std::string ReadFile(const char* filename);

        public:
        Shader(const char* vertexshaderfilename, const char* fragmentshaderfilename);
        GLhandleARB* GetShaderProgram();
    };
    //I didn't put this in the beginning because I just can declare this after defining
    //the subclass
    private:
        Shader *shdControl;
};
#endif

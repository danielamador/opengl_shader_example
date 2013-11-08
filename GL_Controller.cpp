///Created by Daniel Amador dos Santos
///Based on Shader Project example provided by Ole Marius Kohmann
#include <fstream>
#include <cstdlib>
#include "GL_Controller.h"

GL_Controller::GL_Controller(int w, int h)
{
    rotation = 0.0;

    glViewport(0,0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, (GLfloat)(w/h), 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    GLenum glewError = glewInit();
    if(glewError != GLEW_OK)
    {
        std::cout << "Error happened when starting Glew: " << glewGetErrorString(glewError)
                  << std::endl;
    }
}

void GL_Controller::drawCube()
{
     glBegin( GL_QUADS );
                // Top face
                glVertex3f(  1.0f, 1.0f, -1.0f );
                glVertex3f( -1.0f, 1.0f, -1.0f );
                glVertex3f( -1.0f, 1.0f,  1.0f );
                glVertex3f(  1.0f, 1.0f,  1.0f );

                // Bottom face
                glVertex3f(  1.0f, -1.0f, -1.0f );
                glVertex3f( -1.0f, -1.0f, -1.0f );
                glVertex3f( -1.0f, -1.0f,  1.0f );
                glVertex3f(  1.0f, -1.0f,  1.0f );

                // Front face
                glVertex3f(  1.0f,  1.0f, 1.0f );
                glVertex3f( -1.0f,  1.0f, 1.0f );
                glVertex3f( -1.0f, -1.0f, 1.0f );
                glVertex3f(  1.0f, -1.0f, 1.0f );

                // Back face
                glVertex3f(  1.0f, -1.0f, -1.0f );
                glVertex3f( -1.0f, -1.0f, -1.0f );
                glVertex3f( -1.0f,  1.0f, -1.0f );
                glVertex3f(  1.0f,  1.0f, -1.0f );

                // Left face
                glVertex3f( -1.0f,  1.0f,  1.0f);
                glVertex3f( -1.0f,  1.0f, -1.0f);
                glVertex3f( -1.0f, -1.0f, -1.0f);
                glVertex3f( -1.0f, -1.0f,  1.0f);

                // Right face
                glVertex3f(  1.0f,  1.0f,  1.0f);
                glVertex3f(  1.0f,  1.0f, -1.0f);
                glVertex3f(  1.0f, -1.0f, -1.0f);
                glVertex3f(  1.0f, -1.0f,  1.0f);
        glEnd();

}

void GL_Controller::loadShaders(const char* vertshadefile, const char* fragshadefile)
{
    shdControl = new Shader(vertshadefile, fragshadefile);
}


void GL_Controller::rotateModel()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(-2,-2,-10,   0,0,0,   0,1,0);
        glRotatef(rotation, 0, 1, 0);
        rotation += 1;
}

/*Defining Shader's methods
#I usually like to define the constructor first but since it needs defining
#ReadFile and PrintInfoLog first, this time I did differently
*/

std::string GL_Controller::Shader::ReadFile(const char* filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if(in)
    {
        std::string content;
        in.seekg(0, std::ios::end);
        content.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&content[0], content.size());
        in.close();
        return(content);
    }
    return 0;
};

void GL_Controller::Shader::printInfoLog(GLhandleARB obj)
{
    int infologlength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB,
                              &infologlength);

    if(infologlength > 0)
    {
        infoLog = (char*)malloc(infologlength);
        glGetInfoLogARB(obj, infologlength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
    }
};

GL_Controller::Shader::Shader(const char* vsfn, const char* fsfn)
{
    vertexShader   = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

    std::string vertexShaderSource   = ReadFile(vsfn);
    std::string fragmentShaderSource = ReadFile(fsfn);

    const char* v = vertexShaderSource.c_str();
    const char* f = fragmentShaderSource.c_str();

    glShaderSourceARB(vertexShader, 1, &v, NULL);
    glShaderSourceARB(fragmentShader, 1, &f, NULL);

    glCompileShaderARB(vertexShader);
    glCompileShaderARB(fragmentShader);

    printInfoLog(vertexShader);
    printInfoLog(fragmentShader);

    shaderProgram = glCreateProgramObjectARB();
    glAttachObjectARB(shaderProgram, vertexShader);
    glAttachObjectARB(shaderProgram, fragmentShader);

    glLinkProgramARB(shaderProgram);
    printInfoLog(shaderProgram);

    glUseProgramObjectARB(shaderProgram);
}

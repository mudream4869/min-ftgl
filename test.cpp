#include <cstdlib>
#include <cstdio>

#ifdef __APPLE__
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>
#elif __FreeBSD__ || __linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#elif _WIN32
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL\glut.h>
#include <windows.h>
#endif

#include "minftgl.h"

using minftgl::Font;
using minftgl::Label;

Font* font;
Label* label1;
Label* label2;
Label* label3;

void InitResource(){
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    font = new Font("fonts/test.ttf");
    label1 = new Label(L"中字你我他", font);
    label2 = new Label(L"!@#$%^&*(()_", font);
    label3 = new Label(L"abcdefghijk", font, {125, 125, 0});
    return;
}

void Display(){
    label1->Render(0, 0);
    label2->Render(-0.5, -0.5);
    label3->Render(-1, 0);
    glutSwapBuffers();
    return;
}

void CloseFunc(){
    delete label1;
    delete label2;
    delete label3;
    exit(0);
}

int main(int argc, char* argv[]){
    minftgl::Init();
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("ftgl test");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA); 
    glutDisplayFunc(Display);

#ifdef __APPLE__
    glutWMCloseFunc(CloseFunc);
#endif

    InitResource();
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glutMainLoop();

    return 0;

}

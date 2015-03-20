#include <cstdlib>
#include <cstdio>

#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>
#include "minftgl.h"

using minftgl::Font;
using minftgl::Label;

Font* font;
Label* label1;
Label* label2;

void InitResource(){
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    font = new Font("fonts/test1.ttf");
    label1 = new Label(L"中字你我他", font);
    label2 = new Label(L"哈哈哈Test12[ ]1", font);
    return;
}

void Display(){
    label1->Render(0, 0);
    label2->Render(-0.5, -0.5);
    glutSwapBuffers();
    return;
}

void CloseFunc(){
    delete label1;
    delete label2;
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
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glutMainLoop();

    return 0;

}

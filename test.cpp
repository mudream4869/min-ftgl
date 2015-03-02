#include <cstdlib>
#include <cstdio>

#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>
#include "minftgl.h"

using minftgl::Font;
using minftgl::Label;

Font* font;
Label* label;

void InitResource(){
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    font = new Font("fonts/test1.ttf");
    label = new Label(L"中文字測試", font);
    return;
}

void Display(){
    fprintf(stderr, "r");
    label->Render(1, 1);
    return;
}

void CloseFunc(){
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

    glutMainLoop();

    return 0;

}

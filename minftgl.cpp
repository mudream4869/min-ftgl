#include <cstdio>
#include <cstdlib>
#include <string>

#include <ft2build.h>
#include <freetype.h>
#include <vector>

#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>

#include "minftgl.h"

static FT_Library __global_library;

struct preFace{
    FT_Face cont;
};

struct WordPack{
    GLuint id;
    int dx, dy;
    int w, h;
};

struct preData{
    std::vector<WordPack> words;
};

void minftgl::Init(){
    int err = FT_Init_FreeType(&__global_library);
    if(err){
        fprintf(stderr, "minftgl : Library init error\n");
        exit(1);
    }
    return;
}

minftgl::Font::Font(const char* font_path){
    face = new preFace;
    int err = FT_New_Face(__global_library, font_path, 0, &face->cont);
    if(err == FT_Err_Unknown_File_Format){
        fprintf(stderr, "minftgl::Font : Unknow file format\n");
        exit(1);
    }else if(err){
        fprintf(stderr, "minftgl::Font : Unknow err\n");
        exit(1);
    }
    FT_Set_Char_Size(face->cont, 0, 60 << 6, 96, 96);
    return;

}

minftgl::Font::~Font(){
    delete face;
}

minftgl::Label::Label(const wchar_t* str, Font* font){
    int pen_x = 0, pen_y = 0;
    auto slot = font->face->cont->glyph;
    data = new preData;
    for(int lx = 0;str[lx] != 0;lx++){
        unsigned int ch = str[lx];
        int error = FT_Load_Char(font->face->cont, (unsigned int)ch, FT_LOAD_RENDER);
        if(error) continue;
        WordPack wp;
        wp.dx = pen_x + slot->bitmap_left;
        wp.dy = pen_y;
        wp.w = slot->bitmap.width;
        wp.h = slot->bitmap.rows;
        pen_x += slot->advance.x >> 6;
        glGenTextures(1, &wp.id);
        glBindTexture(GL_TEXTURE_2D, wp.id);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        int w = wp.w, h = wp.h;
        unsigned char* buf = new unsigned char[4*w*h];
        for(int ly = 0;ly < h; ly++){
            for(int lx = 0;lx < w;lx++){
                unsigned char val =  slot->bitmap.buffer[lx + w*ly];
                buf[(4*lx + (h-ly-1)*w*4)  ] = 0xFF;
                buf[(4*lx + (h-ly-1)*w*4)+1] = 0xFF;
                buf[(4*lx + (h-ly-1)*w*4)+2] = 0xFF;
                buf[(4*lx + (h-ly-1)*w*4)+3] = val;
            }
        }
        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buf);
        data->words.push_back(wp);
        delete[] buf;
    }
    return;
}

minftgl::Label::~Label(){
    for(auto& wp : data->words)
        glDeleteTextures(1, &wp.id);
    delete data;
    return;
}

void minftgl::Label::Render(double left, double top){
    for(auto& wp : data->words){
        float x = wp.dx/(float)600 + left, y = wp.dy/(float)600 + top;
        float draw_width = wp.w/(float)600, draw_height = wp.h/(float)600;
        float xs[] = {x, x + draw_width, x + draw_width, x};
        float xc[] = {0, 1, 1, 0};
        float ys[] = {y, y, y + draw_height, y + draw_height};
        float yc[] = {0, 0, 1, 1};
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, wp.id);
        glBegin(GL_POLYGON);
        for(int lx = 3;lx >= 0;lx--){
            xs[lx] = xs[lx], ys[lx] = ys[lx];
            glTexCoord2d((GLfloat)(xc[lx]), (GLfloat)(yc[lx]));
            glVertex3f((GLfloat)(xs[lx]), (GLfloat)(ys[lx]), 1);
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    return;
}

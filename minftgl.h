#ifndef INCLUDE_MINFTGL_H
#define INCLUDE_MINFTGL_H
#include <cwchar>
#include <string>
struct preFace;
struct preData;

namespace minftgl{
    
    class Font{
    public:
        Font(const char* font_path, int height = 60);
        ~Font();
        preFace* face;
    };
    
    class Label{
    public:
        Label(const wchar_t* str, Font* font);
        ~Label();
        void Render(double left, double top);
        preData* data;
    }; 

    void Init();
};

#endif

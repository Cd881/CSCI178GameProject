#ifndef _TEXTURELOADER_H
#define _TEXTURELOADER_H

#include <_common.h>
#include <SOIL.h>


class _textureLoader
{
    public:
        _textureLoader();
        virtual ~_textureLoader();

        int width, height; //image width and height
        unsigned char* image; // temp storage for image
        GLuint tex; // openGL texture handler

        void loadTexture(char*);
        void bindTexture();

    protected:

    private:
};

#endif // _TEXTURELOADER_H

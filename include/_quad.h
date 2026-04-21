#ifndef _QUAD_H
#define _QUAD_H

#include <_common.h>
#include <_textureLoader.h>


class _quad
{
    public:
        _quad();
        virtual ~_quad();

        vec3 rot,
             pos,
             scale;

        void drawQuad();
        void initQuad(char*);
        void updateQuad();

        GLuint vboPos, vboTex;

       _textureLoader* myTex = nullptr;

        float xMin = 0.0,
              xMax = 1.0,
              yMin = 0.0,
              yMax = 1.0;

        float verticies[12] = {1.0, 1.0, 0.0, //top right
                               1.0, -1.0, 0.0, //bottom right
                               -1.0, -1.0, 0.0, //bottom left
                               -1.0, 1.0, 0.0}; //top left
        float texCoord[8] = {xMax, yMin,
                             xMax, yMax,
                             xMin, yMax,
                             xMin, yMin};

    protected:

    private:
};

#endif // _QUAD_H

#ifndef _PARALLAX_H
#define _PARALLAX_H
#include <_common.h>
#include <_textureLoader.h>

class _parallax
{
    public:
        _parallax();
        virtual ~_parallax();

        _textureLoader* background  = new _textureLoader();
        _textureLoader* background2 = new _textureLoader(); // NEW second layer

        void initPrlx(char* filename);
        void initPrlx2(char* filename);  // NEW init second layer
        void scroll(bool, int, float);
        void drawBackground(float w, float h);

        float xMax, xMin, yMax, yMin;
        float x2Max, x2Min, y2Max, y2Min; // NEW second layer scroll values
        bool  hasLayer2;                   // NEW flag

        enum{LEFT, RIGHT, UP, DOWN};
        vec3  scale;
        float depth;

    protected:
    private:
};

#endif // _PARALLAX_H

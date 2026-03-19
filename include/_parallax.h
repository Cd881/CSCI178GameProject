#ifndef _PARALLAX_H
#define _PARALLAX_H

#include <_common.h>
#include <_textureLoader.h>

class _parallax
{
    public:
        _parallax();
        virtual ~_parallax();

        _textureLoader* background = new _textureLoader();

        void initPrlx(char* filename);
        void scroll(bool, int, float);
        void drawBackground(float w, float h);

        float xMax, xMin, yMax, yMin;
        enum{LEFT, RIGHT, UP, DOWN};

    protected:

    private:
};

#endif // _PARALLAX_H

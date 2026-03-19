#ifndef _MODEL_H
#define _MODEL_H

#include <_common.h>
#include <_textureLoader.h>

class _model
{
    public:
        _model();
        virtual ~_model();

        vec3 pos;
        vec3 rotation;
        vec3 scale;

        _textureLoader *myImage = new _textureLoader();

        void initModel(char*);
        void drawModel();

    protected:

    private:
};

#endif // _MODEL_H

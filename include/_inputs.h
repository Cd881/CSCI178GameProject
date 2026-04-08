#ifndef _INPUTS_H
#define _INPUTS_H

#include <_common.h>
#include <_model.h>
#include <_modelVBO.h>
#include <_player.h>

class _inputs
{
    public:
        _inputs();
        virtual ~_inputs();

        void keyPressed(_model*);//dont need
        void keyPressed(_modelVBO*);//dont need
        void keyPressed(_player*);
        void keyUP();
        void keyUp(_player*);

        void mouseEventDown(_model*,double, double);
        void mouseEventUp();
        void mouseMove(_model*,double, double);
        void mouseWheel(_model*,double);
        void mouseEventDown(_modelVBO*,double, double);
        void mouseMove(_modelVBO*,double, double);
        void mouseWheel(_modelVBO*,double);

        double prevMx;
        double prevMy;

        bool keys[256];

        bool isTranslate;
        bool isRotation;
        bool isPressedLeft;
        bool isPressedRight;

        WPARAM wParam;
    protected:

    private:
};

#endif // _INPUTS_H

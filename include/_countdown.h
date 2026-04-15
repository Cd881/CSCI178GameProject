#ifndef _COUNTDOWN_H
#define _COUNTDOWN_H

#include <_common.h>
#include <_quad.h>


class _countdown:public _quad
{
    public:
        _countdown();
        virtual ~_countdown();

        int xFrames, yFrames;
        void countDownInit(int,int,char*);
        void countIncrease();
        void countReset();
        void drawCount();

    protected:

    private:
};

#endif // _COUNTDOWN_H

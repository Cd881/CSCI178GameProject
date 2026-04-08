#ifndef _PLAYER_H
#define _PLAYER_H

#include <_common.h>
#include <_quad.h>

class _player:public _quad
{
    public:
        _player();
        virtual ~_player();

        float timer = 0.0;
        int xFrames, yFrames;
        int actionTrigger;
        enum{STAND, LEFTWALK, RIGHTWALK, UPWALK, BACKWALK, RUN, JUMP, ATTACK};

        void playerInit(int,int,char*);
        void playerActions(float);
        void reset();

        float speed;

    protected:

    private:
};

#endif // _PLAYER_H

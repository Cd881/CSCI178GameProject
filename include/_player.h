#ifndef _PLAYER_H
#define _PLAYER_H
#include <_common.h>
#include <_quad.h>
#include <_bullets.h>

class _player:public _quad
{
    public:
        _player();
        virtual ~_player();
        float timer = 0.0;
        float shootTimer = 0.0f;
        int xFrames, yFrames;
        int actionTrigger;
        enum{STAND, LEFTWALK, RIGHTWALK, UPWALK, BACKWALK, RUN, JUMP, ATTACK};
        void playerInit(int, int, char*);
        void playerActions(float);
        void reset();
        float speed;
        _bullets bullets[10];     // 10 bullets on screen
        void shootBullet();
    protected:
    private:
};

#endif // _PLAYER_H

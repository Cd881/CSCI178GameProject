#ifndef _ENEMY_H
#define _ENEMY_H

#include <_common.h>
#include <_quad.h>

class _enemy:public _quad
{
    public:
        _enemy();
        virtual ~_enemy();

        float timer =0;
        int xFrames,yFrames;
        int actionTrigger;
        enum{STAND,LEFTWALK,RIGHTWALK,RUN,JUMP,ATTACK,ROLLEFT,ROLRIGHT,DEAD};

        void enemyInit(int,int,char*);
        void enemyActions(float);
        void placeEnemy(vec3);
        void drawEnemy();
        void reset();

        bool isEnmsLive = true;
        int deadFrames; //how many frames enm has been dead
        float speed;

        float vel = 0,
              t = 0,
              theta = 0;

    protected:

    private:
};

#endif // _ENEMY_H

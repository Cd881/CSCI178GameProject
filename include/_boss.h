#ifndef _BOSS_H
#define _BOSS_H

#include <_common.h>
#include <_quad.h>

class _boss:public _quad
{
    public:
        _boss();
        virtual ~_boss();

        float timer =0, timer2 = 0;
        int xFrames,yFrames;
        int actionTrigger;
        enum{IDLE,MOVING,MOVINGBACK,ATTACK,DEAD};

        void bossInit(int,int,char*);
        void bossActions(float, vec3);//deltatime, player position
        void placeBoss(vec3);
        void drawBoss();
        void reset();

        bool isBossLive = true;
        int deadFrames; //how many frames enm has been dead
        int attackCounter, maxAttacks;
        int health;
        float speed;
        bool moving, canDamage;

    protected:

    private:
};

#endif // _BOSS_H

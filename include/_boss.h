#ifndef _BOSS_H
#define _BOSS_H
#include <_common.h>
#include <_quad.h>
#include <_bullets.h>

class _boss:public _quad
{
    public:
        _boss();
        virtual ~_boss();
        float timer = 0, timer2 = 0;
        int xFrames, yFrames;
        int actionTrigger;
        enum{IDLE, MOVING, MOVINGBACK, ATTACK, DEAD};
        void bossInit(int, int, char*);
        void bossActions(float, vec3);
        void placeBoss(vec3);
        void drawBoss();
        void reset();
        bool isBossLive = true;
        int deadFrames = 0;
        int attackCounter, maxAttacks;
        int health;
        float speed;
        bool moving, canDamage;
        bool justFired = false;   // NEW
        _bullets lasers[10];         // 10 lasers
        float aggressionTimer = 0;   // how often boss attacks
        int attackPhase = 0;         // increases as health drops
    protected:
    private:
};

#endif // _BOSS_H

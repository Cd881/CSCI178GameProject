#ifndef _BULLETS_H
#define _BULLETS_H
#include <_common.h>
#include <_quad.h>

class _bullets:public _quad
{
    public:
        _bullets();
        virtual ~_bullets();
        bool isLive = false;
        int actionTrigger = 0;
        float timer = 0;
        float t = 0;
        float xFrames = 1.0, yFrames = 1.0;
        float spinAngle = 0.0f;
        vec3 dest;
        vec3 source;
        enum{IDLE, ACTIVE, HIT};
        void initBlt(int x, int y, char *filename);
        void update(vec3 pos);
        void shoot(vec3 source, vec3 des, float);
        void bulletActions();
        void drawBlt();
        void drawLaser();
        void drawLaserEnemy();   // NEW - red boss/enemy laser
    protected:
    private:
        void drawFilledCircle(float radius, int segments);
        void drawCircle(float radius, int segments);
};

#endif // _BULLETS_H


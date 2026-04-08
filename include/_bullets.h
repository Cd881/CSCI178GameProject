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
        float timer;
        float t = 0;//for parametric equation
        float xFrames = 1.0, yFrames = 1.0;

        vec3 dest;//to keep track of first destination

        enum{IDLE,ACTIVE,HIT};

        void initBlt(int x, int y, char *filename);
        void update(vec3 pos);
        void shoot(vec3 source,vec3 des,float);
        void bulletActions();
        void drawBlt();

    protected:

    private:
};

#endif // _BULLETS_H

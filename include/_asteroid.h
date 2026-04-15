#ifndef _ASTEROID_H
#define _ASTEROID_H

#include <_common.h>
#include <_quad.h>
#include <_collisioncheck.h>

class _asteroid:public _quad
{
    public:
        _asteroid();
        virtual ~_asteroid();

        _textureLoader *altTex = new _textureLoader();

        float speed; //speed of asteroid
        bool isHit;  //flag for when hit by player
        int hitDir;  //actionTrigger
        vec2 dirVec; //direction vector, that it has been hit at
        int rotFlag;//rotation dir (1,0, or -1) when hit
        enum {LEFT, RIGHT, UP, UPLEFT, UPRIGHT, NONE, HIT, IDLE};

        vec2 vel;

        void getAsteroidTex(int);
        void initAsteroid(int,char*);
        void drawAsteroid();
        void animate(float);
        void reset();

    protected:

    private:
};

#endif // _ASTEROID_H

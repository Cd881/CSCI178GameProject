#include "_player.h"

_player::_player()
{
    xMin = 0;
    xMax = 1.0;
    yMin = 0;
    yMax = 1.0;
    pos.y = -3.2;
    pos.z = -12;
    scale.x = 0.7;
    scale.y = 0.7;
    actionTrigger = STAND;
    shootTimer = 0.0f;
}

_player::~_player()
{
    //dtor
}

void _player::playerInit(int x, int y, char* filename)
{
    initQuad(filename);
    xFrames = x;
    yFrames = y;
    xMin = 0;
    xMax = 1.0/(float)xFrames;
    yMax = 1.0/(float)yFrames;
    yMin = 0;
    speed = 5.5;

    for(int i = 0; i < 10; i++)
        bullets[i].initBlt(1, 1, NULL);
}

void _player::shootBullet()
{
    for(int i = 0; i < 10; i++)
    {
        if(!bullets[i].isLive)
        {
            vec3 src;
            src.x = pos.x;
            src.y = pos.y + 0.5f;
            src.z = pos.z;

            vec3 dst;
            dst.x = pos.x + ((rand()%3 - 1) * 0.1f); // tiny spread
            dst.y = pos.y + 20.0f;
            dst.z = pos.z;

            bullets[i].dest      = dst;
            bullets[i].source    = src;
            bullets[i].pos       = src;
            bullets[i].t         = 0.0f;
            bullets[i].spinAngle = 0.0f;
            bullets[i].actionTrigger = _bullets::ACTIVE;
            bullets[i].isLive    = true;
            break;
        }
    }
}

void _player::playerActions(float deltaTime)
{
    timer      += deltaTime;
    shootTimer += deltaTime;

    // Update bullets
    for(int i = 0; i < 10; i++)
    {
        if(bullets[i].isLive)
        {
            bullets[i].shoot(bullets[i].source, bullets[i].dest, deltaTime);
            bullets[i].bulletActions();
        }
    }

    switch(actionTrigger)
    {
    case STAND:
        if(rot.z > 0)      rot.z -= 90 * deltaTime;
        else if(rot.z < 0) rot.z += 90 * deltaTime;
        if(timer > 0.25)
        {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            timer = 0;
        }
        break;

    case LEFTWALK:
        if(rot.z < 15)   rot.z += 90 * deltaTime;
        if(pos.x > -7.5) pos.x -= speed * deltaTime;
        if(timer > 0.08)
        {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            timer = 0;
        }
        break;

    case RIGHTWALK:
        if(rot.z > -15) rot.z -= 90 * deltaTime;
        if(pos.x < 7.5) pos.x += speed * deltaTime;
        if(timer > 0.08)
        {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            timer = 0;
        }
        break;

    default: break;
    }
}

void _player::reset()
{
    rot.z = 0;
    pos.x = 0;
    actionTrigger = STAND;

    for(int i = 0; i < 10; i++)
    {
        bullets[i].isLive = false;
        bullets[i].actionTrigger = _bullets::IDLE;
        bullets[i].t = 0.0f;
        bullets[i].spinAngle = 0.0f;
    }
}

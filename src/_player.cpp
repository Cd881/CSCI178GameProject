#include "_player.h"

_player::_player()
{
    xMin = 0;
    xMax = 1.0;
    yMin = 0;
    yMax = 1.0;

    pos.y = -1.2;
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

    xMin = 0.0;
    xMax = 1.0/(float)xFrames;
    yMin = 0.0;
    yMax = 1.0/(float)yFrames;

    pos.z = -25.0;
    pos.y = -6.8;

    yMin = yMax*2.0;
    yMax += yMax*2.0;
}

void _player::playerActions(float deltaTime)
{
    timer += deltaTime;
    switch(actionTrigger) {
    case STAND:
        xMin = 0.0;
        xMax = 1.0/(float)xFrames;
        yMin = yMax-1.0/(float)yFrames;
        yMax = 1.0/(float)yFrames;
        break;
    case LEFTWALK:
        if(timer>0.15) {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            yMin = 1.0/4.0;
            yMax = 1.0/2.0;
            timer = 0;
        }
        break;
    case RIGHTWALK:
        if(timer>0.15) {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            yMin = 1.0/2.0;
            yMax = 3.0/4.0;
            timer = 0;
        }
        break;
    case UPWALK:
        if(timer>0.15) {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            yMin = 3.0/4.0;
            yMax = 1.0;
            timer = 0;
        }
        break;
    case BACKWALK:
        if(timer>0.15) {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            yMin = 0.0;
            yMax = 1.0/4.0;
            timer = 0;
        }
    break;
    default: break;
    }
}

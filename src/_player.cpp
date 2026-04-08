#include "_player.h"

_player::_player()
{
    xMin = 0;
    xMax = 1.0;
    yMin = 0;
    yMax = 1.0;

    pos.y = -2.2;
    pos.z = -12;
    scale.x = 0.7;
    scale.y = 0.7;

    actionTrigger = STAND;
}

_player::~_player()
{
    //dtor
}

void _player::playerInit(int x, int y, char* filename)
{
    initQuad(filename);
    xFrames =x;
    yFrames =y;

    xMin =0;
    xMax =1.0/(float)xFrames;
    yMax =1.0/(float)yFrames;
    yMin =0;

    speed = 5.5;
}

void _player::playerActions(float deltaTime)
{
    timer += deltaTime;
    switch(actionTrigger) {
    case STAND:
        //does make it bouce a little
        //but it looks like the rocket is actually boosting
        if(rot.z > 0) rot.z -= 90 * deltaTime;
        else if(rot.z < 0) rot.z += 90 * deltaTime;
        if(timer>0.25) {
            xMin +=1.0/(float)xFrames;
            xMax +=1.0/(float)xFrames;
            timer =0;
        }
        break;
    case LEFTWALK:
        if(rot.z < 15) rot.z += 90 * deltaTime;

        if(pos.x > -7.5) pos.x -= speed*deltaTime;
        if(timer>0.08) {
            xMin +=1.0/(float)xFrames;
            xMax +=1.0/(float)xFrames;

          timer =0;
         }
         break;
    case RIGHTWALK:
        if(rot.z > -15) rot.z -= 90 * deltaTime;

        if(pos.x < 7.5) pos.x += speed*deltaTime;
        if(timer>0.08) {
            xMin +=1.0/(float)xFrames;
            xMax +=1.0/(float)xFrames;

            timer =0;
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
}

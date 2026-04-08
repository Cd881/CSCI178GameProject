#include "_bullets.h"

_bullets::_bullets()
{
    //ctor
    pos.x = 0;
    pos.y = -4;
    pos.z = -6.99;

    rot.x = 0;
    rot.y = 0;
    rot.z = 0;

    scale.x = 0.2;
    scale.y = 0.2;
    scale.z = 1;

    actionTrigger = IDLE;
}

_bullets::~_bullets()
{
    //dtor
}

void _bullets::initBlt(int x, int y, char* filename)
{
    initQuad(filename);
    xFrames = x;
    yFrames = y;

    xMin = 0.0;
    xMax = 1.0/(float)xFrames;
    yMin = 0.0;
    yMax = 1.0/(float)yFrames;
}

void _bullets::update(vec3 pos)
{
    //TODO:: depends on use of bullets
}

void _bullets::shoot(vec3 source, vec3 des, float deltaTime)
{
    if(actionTrigger == IDLE) {
        dest = des;

        //Translate to the center
        float x = -source.x + des.x,
              y = -source.y + des.y;

        des.x >= 0 ? rot.z = atan((y/x)*180.0/PI)+90:rot.z = atan((y/x)*180.0/PI)-90;

        //angle between two points
        //arccos(dot product of the points)
        /*float x = source.x * dest.x,
              y = source.y * dest.y,
              z = source.z * dest.z,
              MS = sqrt(pow(source.x,2)+pow(source.y,2)+pow(source.z,2)), //mag of source
              MD = sqrt(pow(dest.x,2)+pow(dest.y,2)+pow(dest.z,2)); //mag of dest

        rot.z = acos((x + y + z) / (MS * MD));*/
    }

    if(isLive) {
        timer += deltaTime;

        if(timer > 0.08){
            pos.x = source.x + t*(dest.x - source.x);
            pos.y = source.y + t*(dest.y - source.y);
            //pos.z = source.z + t*(dest.z - source.z);

            if(actionTrigger == ACTIVE) {
                if(t > 1) { //reset blt
                    t = 0;
                    actionTrigger = IDLE;
                } else t += deltaTime+0.1;
            }

            timer = 0;
        }
    }
}

void _bullets::bulletActions()
{
    switch(actionTrigger) {
    case IDLE: //bullet is stored
        isLive = false;
        break;
    case ACTIVE: //bullet is on the move
        isLive = true;
        break;
    case HIT: //bullet hit target or out of bounds
        isLive = false;
        break;
    default: break;
    }
}

void _bullets::drawBlt()
{
    if(isLive) {
        updateQuad();
        drawQuad();
    }
}

#include "_enemy.h"

_enemy::_enemy()
{
    xMin = 0;
    xMax = 1.0;
    yMin = 0;
    yMax = 1.0;

    pos.x = 0;
    pos.y = -1.2;
    pos.z = -7;

    rot.x = 0;
    rot.y = 0;
    rot.z = 0;

    scale.x = 0.5;
    scale.y = 0.5;
    scale.z = 1.0;

    isEnmsLive = true;

    actionTrigger = STAND;
    speed = 2;
}

_enemy::~_enemy()
{
    //dtor
}

void _enemy::enemyInit(int x, int y, char* filename)
{
    initQuad(filename);
    xFrames = x;
    yFrames = y;

    xMin = 0.0;
    xMax = 1.0/(float)xFrames;
    yMin = 0.0;
    yMax = 1.0/(float)yFrames;

    pos.z = -12.0;
    pos.x = (float)((rand()%40) - 21.0)/4.0;
    pos.y = ((float)((rand()%24) - 13.0)/4.0) + 12.0;
}

void _enemy::enemyActions(float deltaT)
{
    timer += deltaT;
    switch(actionTrigger)
    {
        case STAND: //fly down
            if(pos.y <= -5) {
                pos.x = ((float)((rand()%40) - 20.0)/4.0);
                pos.y = ((float)((rand()%24) - 12.0)/4.0) + 10.0;
            } else pos.y -= speed * deltaT;
            if(timer>0.08) {
                xMin +=1.0/(float)xFrames;
                xMax +=1.0/(float)xFrames;

                timer =0;
            }
            /*xMin =0;
            xMax =1.0/(float)xFrames;
            yMax = 1.0/(float)yFrames;
            yMin = yMax-(1.0/(float)yFrames);*/
            break;
        case DEAD:
            if(deadFrames <= 4) {
                if(timer>0.08) {
                    xMin +=1.0/(float)xFrames;
                    xMax +=1.0/(float)xFrames;
                    yMin = 1.0/(float)yFrames;
                    yMax = 1.0;

                    deadFrames++;
                    timer =0;
                }
            } else {
                pos.x = ((float)((rand()%40) - 20.0)/4.0);
                pos.y = ((float)((rand()%24) - 12.0)/4.0) + 10.0;
                actionTrigger = STAND;
                isEnmsLive = true;
                deadFrames = 0;
                yMin = 0.0;
                yMax = 1.0/(float)yFrames;
            }
            break;
        default: break;
    }
}

void _enemy::placeEnemy(vec3 newPos)
{
    pos.x = newPos.x;
    pos.y = newPos.y;
    pos.z = newPos.z;
}

void _enemy::drawEnemy()
{
    updateQuad();
    drawQuad();
}

void _enemy::reset()
{
    pos.z = -12.0;
    pos.x = (float)((rand()%40) - 21.0)/4.0;
    pos.y = ((float)((rand()%24) - 13.0)/4.0) + 12.0;
}

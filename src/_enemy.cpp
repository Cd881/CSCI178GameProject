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

    actionTrigger = 2;
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

    pos.z = -25.0;
    pos.y = -6.8;

    vel = 30;
    t = 0.1;
}

void _enemy::enemyActions(float deltaTime)
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
        if(timer>0.08) {
            xMax > xMin ? (xMax = 0.0, xMin = 1.0/(float)xFrames) : NULL;

            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            yMin = 0.0;
            yMax = 0.5;

            pos.x >= -16 ? pos.x -= 3*deltaTime+0.2 : actionTrigger = RIGHTWALK;

            timer = 0;
        }
        break;
    case RIGHTWALK:
        if(timer>0.08) {
            xMax < xMin ? (xMin = 0.0, xMax = 1.0/(float)xFrames) : NULL;

            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            yMin = 0.0;
            yMax = 0.5;

            pos.x <= 16 ? pos.x += 3*deltaTime+0.2 : actionTrigger = LEFTWALK;

            timer = 0;
        }
        break;
    case ROLLEFT:
        if(timer>0.08) {
            theta = 30.0*(PI/180.0);

            rot.z += 12.0;

            //x = vtcos
            //y = vtsin - (1/2)gt^2
            pos.x -= vel*t*cos(theta)/400.0;
            pos.y += (vel*t*sin(theta)+0.5*GRAV*t*t)/40.0;

            pos.y > -6.8 ? t += 0.3 : (t=0.1, pos.y = -6.8);
            pos.x < -18 ? (actionTrigger=RIGHTWALK, pos.y = -6.8, rot.z = 0):NULL;

            timer = 0;
        }
        break;
    case ROLRIGHT:
        if(timer>0.08) {
            theta = 30.0*(PI/180.0);

            rot.z -= 12.0;

            //x = vtcos
            //y = vtsin - (1/2)gt^2
            pos.x += vel*t*cos(theta)/400.0;
            pos.y += (vel*t*sin(theta)+0.5*GRAV*t*t)/40.0;

            pos.y > -6.8 ? t += 0.3 : (t=0.1, pos.y = -6.8);
            pos.x > 18 ? (actionTrigger=LEFTWALK, pos.y = -6.8, rot.z = 0):NULL;

            timer = 0;
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

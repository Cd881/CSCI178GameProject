#include "_asteroid.h"

_asteroid::_asteroid()
{
    //ctor
    isHit = false;
    hitDir = NONE;
    scale.x = 0.5;
    scale.y = 0.5;
}

_asteroid::~_asteroid()
{
    //dtor
    delete altTex;
}

void _asteroid::getAsteroidTex(int index)//get which asteroid texture to use
{
    switch(index) {//chatGPT did not space them evenly
    case 0:
        xMin = 0;
        xMax = 0.25;
        yMin = 0;
        yMax = 0.25;
        break;
    case 1:
        xMin = 0.25;
        xMax = 0.5;
        yMin = 0;
        yMax = 0.25;
        break;
    case 2:
        xMin = 0.5;
        xMax = 0.75;
        yMin = 0;
        yMax = 0.25;
        break;
    case 3:
        xMin = 0.75;
        xMax = 1.0;
        yMin = 0;
        yMax = 0.25;
        break;
    case 4:
        xMin = 0;
        xMax = 0.25;
        yMin = 0.24;
        yMax = 0.49;
        break;
    case 5:
        xMin = 0.25;
        xMax = 0.5;
        yMin = 0.24;
        yMax = 0.49;
        break;
    case 6:
        xMin = 0.5;
        xMax = 0.75;
        yMin = 0.24;
        yMax = 0.49;
        break;
    case 7:
        xMin = 0.75;
        xMax = 1.0;
        yMin = 0.24;
        yMax = 0.49;
        break;
    case 8:
        xMin = 0;
        xMax = 0.25;
        yMin = 0.45;
        yMax = 0.7;
        break;
    case 9:
        xMin = 0.25;
        xMax = 0.5;
        yMin = 0.45;
        yMax = 0.7;
        break;
    case 10:
        xMin = 0.5;
        xMax = 0.75;
        yMin = 0.45;
        yMax = 0.7;
        break;
    case 11:
        xMin = 0.75;
        xMax = 1.0;
        yMin = 0.45;
        yMax = 0.7;
        break;
    case 12:
        xMin = 0;
        xMax = 0.25;
        yMin = 0.7;
        yMax = 0.95;
        break;
    case 13:
        xMin = 0.25;
        xMax = 0.5;
        yMin = 0.7;
        yMax = 0.95;
        break;
    case 14:
        xMin = 0.5;
        xMax = 0.75;
        yMin = 0.7;
        yMax = 0.95;
        break;
    case 15:
        xMin = 0.75;
        xMax = 1.0;
        yMin = 0.7;
        yMax = 0.95;
        break;
    }
}

void _asteroid::initAsteroid(int index, char* filename) {
    initQuad(filename);
    getAsteroidTex(index);

    speed = 1.5 + (float)(rand()%20)/50.0;

    vel.x = 0;
    vel.y = speed;

    float s = 0.3 + (float)(rand()%10)/40.0;
    scale.x = s;
    scale.y = s;

    rot.z = (float)(rand()%180)/2.0;

    rotFlag = rand()%3-1;

    //TODO:: Fix this make the asteroids come more gradually rather than all 15
    //also have to fix it in the reset function
    pos.z = -12.0;
    pos.x = (float)((rand()%40) - 21.0)/4.0;
    pos.y = ((float)((rand()%24) - 13.0)/4.0) + 6.0;
}

void _asteroid::drawAsteroid()
{
    updateQuad();
    drawQuad();
}

void _asteroid::animate(float deltaT)
{
    if(isHit) {
        rot.z += (90 * rotFlag) * deltaT;
        switch(hitDir) {
        // Old janky collision
        /*case UP:
            pos.y += speed * deltaT;
            break;
        case UPRIGHT:
            pos.y += speed * deltaT;
            pos.x += speed * deltaT;
            break;
        case UPLEFT:
            pos.y += speed * deltaT;
            pos.x -= speed * deltaT;
            break;
        case LEFT:
            pos.x -= (speed * 1.5) * deltaT;
            break;
        case RIGHT:
            pos.x += (speed * 1.5) * deltaT;
            break;*/
        case HIT: //better collision
            vel.x = dirVec.x * (speed + 0.1);
            vel.y = dirVec.y * (speed + 0.1);

            pos.x += vel.x * deltaT;
            pos.y += vel.y * deltaT;
            break;
        case NONE:
            isHit = false;
            break;
        default:
            break;
        }
        if(pos.x <= -8 || pos.x >= 8 || pos.y <= -6 || pos.y >= 6) {
            isHit = false;
            hitDir = NONE;
            pos.x = ((float)((rand()%40) - 20.0)/4.0);
            pos.y = ((float)((rand()%24) - 12.0)/4.0) + 10.0;
        }
    } else
        if(hitDir != IDLE) {
            if(pos.y <= -5) {
                pos.x = ((float)((rand()%40) - 20.0)/4.0);
                pos.y = ((float)((rand()%24) - 12.0)/4.0) + 10.0;
            } else {
                pos.y -= speed * deltaT;
            }
        }
}

void _asteroid::reset()
{
    isHit = false;
    hitDir = NONE;

    speed = 1.5 + (float)(rand()%20)/50.0;

    float s = 0.3 + (float)(rand()%10)/40.0;
    scale.x = s;
    scale.y = s;

    pos.z = -12.0;
    pos.x = (float)((rand()%40) - 21.0)/4.0;
    pos.y = ((float)((rand()%24) - 13.0)/4.0) + 6.0;
}

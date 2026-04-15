#include "_boss.h"

_boss::_boss()
{
    xMin = 0;
    xMax = 1.0;
    yMin = 0;
    yMax = 1.0;

    rot.x = 0;
    rot.y = 0;
    rot.z = 0;

    scale.x = 0.65;
    scale.y = 0.65;
    scale.z = 1.0;

    actionTrigger = IDLE;
    health = 5;
    speed = 3;

    attackCounter = 0;
    moving = false;
    canDamage = false;

    isBossLive = true;
}

_boss::~_boss()
{
    //dtor
}

void _boss::bossInit(int x, int y, char* filename)
{
    initQuad(filename);
    xFrames = x;
    yFrames = y;

    xMin = 0.0;
    xMax = 1.0/(float)xFrames;
    yMin = 0.0;
    yMax = 1.0/(float)yFrames;

    pos.z = -12;
    pos.x = 0;
    pos.y = 12;
}

void _boss::bossActions(float deltaTime, vec3 playerPos)
{
    timer += deltaTime;
    timer2 += deltaTime;

    switch(actionTrigger) {
    case IDLE:
        if(timer2 > 0.5) {
            pos.x = (float)((rand()%40) - 21.0)/4.0;
            //60% chance of moving to attack phase
            if(rand()%10 > 3) actionTrigger = MOVING;
            timer2 = 0;
        }
        break;
    case MOVING:
        canDamage = true;
        if(timer > 0.08) {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            timer = 0;
        }
        if(pos.y > 1.2) {
            pos.y -= speed * deltaTime;
            timer2 = 0;
        }
        else {
            if(timer2 > 0.8) {
                actionTrigger = ATTACK;
                maxAttacks = 3 + rand()%3;
                yMin = 1.0/(float)yFrames;
                yMax = 2.0/(float)yFrames;
                canDamage = false;
                timer2 = 0;
            }
        }
        break;
    case MOVINGBACK:
        canDamage = true;
        yMin = 0.0;
        yMax = 1.0/(float)yFrames;
        if(timer > 0.08) {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            timer = 0;
        }
        if(moving) {
            pos.y -= (speed + 3.5) * deltaTime;
            if(pos.y < -5) {
                pos.y = 12;
                actionTrigger = IDLE;
                moving = false;
            }

        } else if(pos.x > playerPos.x) {
            pos.x -= speed * deltaTime;

        } else
            pos.x += speed * deltaTime;

        if(timer2 > 2.5) {
            moving = true;
            timer2 = 0;
        }
        break;
    case ATTACK:
        canDamage = false;
        if(timer > 0.08) {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            timer = 0;
        }
        //TODO:: HERE ADD THE LASER SHOOTING TOWARDS PLAYER
        //Make it fire a random amount from 3-5 shots(use maxAttacks and attackCounter),
        //player pos may change use playerPos for the parametric eq
        //play laser sound there are 2 so randomly select one to play when firing
        //make it fun and look good

        if(timer2 > 1) { //remove this but you need to change action trigger to MOVINGBACK once done attacking
            actionTrigger = MOVINGBACK;
            timer2 = 0;
        }
        break;
    case DEAD:
        canDamage = false;
        if(deadFrames >= 4) {
            isBossLive = false;
            break;
        }
        yMin = 2.0/(float)yFrames;
        yMax = 1.0;
        if(timer > 0.08) {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            deadFrames++;
            timer = 0;
        }
        break;
    default: break;
    }
}

void _boss::placeBoss(vec3)
{

}

void _boss::drawBoss()
{
    updateQuad();
    drawQuad();
}

void _boss::reset()
{
    health = 5;
    isBossLive = true;
    moving = false;
    deadFrames = 0;
    actionTrigger = IDLE;

    pos.y = 12;
}

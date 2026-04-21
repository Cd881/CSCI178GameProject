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
    health = 10;        // more health
    speed = 4.5;        // faster
    attackCounter = 0;
    moving = false;
    canDamage = false;
    isBossLive = true;
    deadFrames = 0;
    attackPhase = 0;
    aggressionTimer = 0;
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

    for(int i = 0; i < 10; i++)
        lasers[i].initBlt(1, 1, NULL);
}

void _boss::bossActions(float deltaTime, vec3 playerPos)
{
    timer        += deltaTime;
    timer2       += deltaTime;
    aggressionTimer += deltaTime;

    // Attack phase increases as health drops — gets more aggressive
    if(health <= 7 && health > 4)       attackPhase = 1;
    else if(health <= 4 && health > 2)  attackPhase = 2;
    else if(health <= 2)                attackPhase = 3;

    // Fire rate based on phase
    float fireRate  = 0.35f - (attackPhase * 0.08f); // 0.35 → 0.11
    float moveSpeed = speed + attackPhase * 1.5f;

    // Update all lasers
    for(int i = 0; i < 10; i++)
    {
        if(lasers[i].isLive)
        {
            lasers[i].shoot(lasers[i].source, lasers[i].dest, deltaTime);
            lasers[i].bulletActions();
        }
    }

    switch(actionTrigger)
    {
    case IDLE:
        // More aggressive — attack 80% of time
        if(aggressionTimer > (0.4f - attackPhase * 0.1f))
        {
            pos.x = (float)((rand()%40) - 21.0)/4.0;
            if(rand()%10 > 2) actionTrigger = MOVING; // 80% chance
            aggressionTimer = 0;
        }
        break;

    case MOVING:
        canDamage = true;
        if(timer > 0.08)
        {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            timer = 0;
        }
        if(pos.y > 1.2)
        {
            pos.y -= moveSpeed * deltaTime;
            timer2 = 0;
        }
        else
        {
            if(timer2 > 0.5f) // less wait before attacking
            {
                actionTrigger = ATTACK;
                // More shots at higher phases
                maxAttacks    = (3 + rand()%3) + attackPhase * 2;
                attackCounter = 0;
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
        if(timer > 0.08)
        {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            timer = 0;
        }
        if(moving)
        {
            pos.y -= (moveSpeed + 3.5f) * deltaTime;
            if(pos.y < -5)
            {
                pos.y = 12;
                actionTrigger = IDLE;
                moving = false;
            }
        }
        else if(pos.x > playerPos.x)
            pos.x -= moveSpeed * deltaTime;
        else
            pos.x += moveSpeed * deltaTime;

        if(timer2 > (2.0f - attackPhase * 0.4f))
        {
            moving = true;
            timer2 = 0;
        }

        // Phase 3 — shoot while moving back too!
        if(attackPhase >= 3 && timer2 > fireRate && attackCounter < 3)
        {
            for(int i = 0; i < 10; i++)
            {
                if(!lasers[i].isLive)
                {
                    lasers[i].source = pos;
                    lasers[i].pos    = pos;

                    vec3 target;
                    target.x = playerPos.x + ((rand()%6 - 3) * 0.15f);
                    target.y = playerPos.y;
                    target.z = playerPos.z;
                    lasers[i].dest = target;

                    lasers[i].t           = 0.0f;
                    lasers[i].spinAngle   = 0.0f;
                    lasers[i].actionTrigger = _bullets::ACTIVE;
                    lasers[i].isLive      = true;
                    attackCounter++;
                    timer2 = 0;
                    break;
                }
            }
        }
        break;

    case ATTACK:
        canDamage = false;
        if(timer > 0.08)
        {
            xMin += 1.0/(float)xFrames;
            xMax += 1.0/(float)xFrames;
            timer = 0;
        }

        // Fire laser every fireRate seconds
        if(timer2 > fireRate && attackCounter < maxAttacks)
        {
            for(int i = 0; i < 10; i++)
            {
                if(!lasers[i].isLive)
                {
                    lasers[i].source = pos;
                    lasers[i].pos    = pos;

                    // Spread gets wider at higher phases
                    float spread = 0.1f + attackPhase * 0.15f;
                    vec3 target;
                    target.x = playerPos.x + ((rand()%10 - 5) * spread);
                    target.y = playerPos.y;
                    target.z = playerPos.z;
                    lasers[i].dest = target;

                    lasers[i].t           = 0.0f;
                    lasers[i].spinAngle   = 0.0f;
                    lasers[i].actionTrigger = _bullets::ACTIVE;
                    lasers[i].isLive      = true;

                    justFired = true;   // NEW — signal scene to play sound

                    attackCounter++;
                    timer2 = 0;
                    break;
                }
            }
        }

        // Done attacking
        if(attackCounter >= maxAttacks && timer2 > 0.3f)
        {
            actionTrigger = MOVINGBACK;
            attackCounter = 0;
            timer2 = 0;
        }
        break;

    case DEAD:
        canDamage = false;
        if(deadFrames >= 4)
        {
            isBossLive = false;
            break;
        }
        yMin = 2.0/(float)yFrames;
        yMax = 1.0;
        if(timer > 0.08)
        {
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
    for(int i = 0; i < 10; i++)
        lasers[i].drawLaserEnemy();

    updateQuad();
    drawQuad();
}

void _boss::reset()
{
    health        = 10;
    isBossLive    = true;
    moving        = false;
    deadFrames    = 0;
    attackCounter = 0;
    attackPhase   = 0;
    aggressionTimer = 0;
    actionTrigger = IDLE;
    pos.y = 12;

    for(int i = 0; i < 10; i++)
    {
        lasers[i].isLive = false;
        lasers[i].actionTrigger = _bullets::IDLE;
        lasers[i].t = 0.0f;
        lasers[i].spinAngle = 0.0f;
    }
}

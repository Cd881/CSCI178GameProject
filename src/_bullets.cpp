#include "_bullets.h"

_bullets::_bullets()
{
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
    spinAngle = 0.0f;
}

_bullets::~_bullets()
{
    //dtor
}

void _bullets::drawFilledCircle(float radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);
        for(int i = 0; i <= segments; i++)
        {
            float angle = 2.0f * PI * i / segments;
            glVertex3f(radius * cos(angle), radius * sin(angle), 0.0f);
        }
    glEnd();
}

void _bullets::drawCircle(float radius, int segments)
{
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < segments; i++)
        {
            float angle = 2.0f * PI * i / segments;
            glVertex3f(radius * cos(angle), radius * sin(angle), 0.0f);
        }
    glEnd();
}

void _bullets::drawLaser()
{
    if(!isLive) return;

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        glRotatef(spinAngle, 0.0f, 0.0f, 1.0f);

        // Outer glow ring
        glColor4f(0.0f, 0.5f, 1.0f, 0.4f);
        drawCircle(0.18f, 24);

        // Mid glow
        glColor4f(0.0f, 0.8f, 1.0f, 0.7f);
        drawFilledCircle(0.13f, 24);

        // Inner bright core
        glColor4f(0.8f, 1.0f, 1.0f, 1.0f);
        drawFilledCircle(0.07f, 24);

        // Specular highlight
        glPushMatrix();
            glTranslatef(-0.03f, 0.03f, 0.0f);
            glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
            drawFilledCircle(0.025f, 16);
        glPopMatrix();

        // Energy spikes
        glLineWidth(2.0f);
        glColor4f(0.0f, 1.0f, 1.0f, 0.9f);
        glBegin(GL_LINES);
            glVertex3f(-0.16f,  0.0f, 0.0f);
            glVertex3f( 0.16f,  0.0f, 0.0f);
            glVertex3f( 0.0f,  -0.16f, 0.0f);
            glVertex3f( 0.0f,   0.16f, 0.0f);
        glEnd();
        glLineWidth(1.0f);

    glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

void _bullets::drawLaserEnemy()
{
    if(!isLive) return;

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        glRotatef(spinAngle, 0.0f, 0.0f, 1.0f);

        // Outer glow - red/orange for enemy
        glColor4f(1.0f, 0.0f, 0.0f, 0.4f);
        drawCircle(0.22f, 24);

        glColor4f(1.0f, 0.3f, 0.0f, 0.7f);
        drawFilledCircle(0.16f, 24);

        glColor4f(1.0f, 0.8f, 0.0f, 1.0f);
        drawFilledCircle(0.09f, 24);

        glPushMatrix();
            glTranslatef(-0.04f, 0.04f, 0.0f);
            glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
            drawFilledCircle(0.03f, 16);
        glPopMatrix();

        glLineWidth(2.5f);
        glColor4f(1.0f, 0.5f, 0.0f, 0.9f);
        glBegin(GL_LINES);
            glVertex3f(-0.20f,  0.0f, 0.0f);
            glVertex3f( 0.20f,  0.0f, 0.0f);
            glVertex3f( 0.0f,  -0.20f, 0.0f);
            glVertex3f( 0.0f,   0.20f, 0.0f);
        glEnd();

        glPushMatrix();
            glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
            glColor4f(1.0f, 0.2f, 0.0f, 0.6f);
            glBegin(GL_LINES);
                glVertex3f(-0.14f, 0.0f, 0.0f);
                glVertex3f( 0.14f, 0.0f, 0.0f);
                glVertex3f( 0.0f, -0.14f, 0.0f);
                glVertex3f( 0.0f,  0.14f, 0.0f);
            glEnd();
        glPopMatrix();
        glLineWidth(1.0f);

    glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

void _bullets::initBlt(int x, int y, char* filename)
{
    if(filename != NULL)
        initQuad(filename);
    xFrames = x;
    yFrames = y;
    xMin = 0.0;
    xMax = 1.0/(float)xFrames;
    yMin = 0.0;
    yMax = 1.0/(float)yFrames;
}

void _bullets::update(vec3 p)
{
    //depends on use
}

void _bullets::shoot(vec3 src, vec3 des, float deltaTime)
{
    if(actionTrigger == IDLE) return;

    // Spin
    spinAngle += 400.0f * deltaTime;
    if(spinAngle > 360.0f) spinAngle -= 360.0f;

    timer += deltaTime;
    if(timer > 0.008f)
    {
        pos.x = src.x + t * (dest.x - src.x);
        pos.y = src.y + t * (dest.y - src.y);
        pos.z = src.z;

        if(actionTrigger == ACTIVE)
        {
            if(t >= 1.0f)
            {
                t = 0.0f;
                actionTrigger = IDLE;
                isLive = false;
            }
            else
                t += deltaTime * 1.8f; // good travel speed
        }
        timer = 0;
    }
}

void _bullets::bulletActions()
{
    switch(actionTrigger)
    {
    case IDLE:
        isLive = false;
        break;
    case ACTIVE:
        isLive = true;
        break;
    case HIT:
        isLive = false;
        break;
    default: break;
    }
}

void _bullets::drawBlt()
{
    if(isLive)
    {
        updateQuad();
        drawQuad();
    }
}

#include "_parallax.h"

_parallax::_parallax()
{
    xMax = 1.0;
    xMin = 0.0;
    yMax = 1.0;
    yMin = 0.0;
    depth = -13;
    scale.x = 5.33;
    scale.y = 5.33;
    scale.z = 1.0;

    // Second layer
    x2Max    = 1.0;
    x2Min    = 0.0;
    y2Max    = 1.0;
    y2Min    = 0.0;
    hasLayer2 = false;
}

_parallax::~_parallax()
{
    delete background;
    delete background2;
}

void _parallax::initPrlx(char* filename)
{
    background->loadTexture(filename);
}

void _parallax::initPrlx2(char* filename)
{
    background2->loadTexture(filename);
    hasLayer2 = true;
}

void _parallax::scroll(bool isAuto, int dir, float speed)
{
    if(isAuto)
    {
        switch(dir)
        {
        case LEFT:
            xMin -= speed;
            xMax -= speed;
            // Second layer scrolls faster for depth effect
            if(hasLayer2) { x2Min -= speed * 1.8f; x2Max -= speed * 1.8f; }
            break;
        case RIGHT:
            xMin += speed;
            xMax += speed;
            if(hasLayer2) { x2Min += speed * 1.8f; x2Max += speed * 1.8f; }
            break;
        case UP:
            yMin -= speed;
            yMax -= speed;
            if(hasLayer2) { y2Min -= speed * 1.8f; y2Max -= speed * 1.8f; }
            break;
        case DOWN:
            yMin += speed;
            yMax += speed;
            if(hasLayer2) { y2Min += speed * 1.8f; y2Max += speed * 1.8f; }
            break;
        default:
            break;
        }
    }
}

void _parallax::drawBackground(float w, float h)
{
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    // ── Layer 1 — slow base background ───────────────────────
    glPushMatrix();
    glScalef(scale.x, scale.y, scale.z);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    background->bindTexture();
    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMax); glVertex3f(-w/h, -1.0, depth);
        glTexCoord2f(xMax, yMax); glVertex3f( w/h, -1.0, depth);
        glTexCoord2f(xMax, yMin); glVertex3f( w/h,  1.0, depth);
        glTexCoord2f(xMin, yMin); glVertex3f(-w/h,  1.0, depth);
    glEnd();
    glPopMatrix();

    // ── Layer 2 — faster semi-transparent overlay ─────────────
    if(hasLayer2)
    {
        glPushMatrix();
        glScalef(scale.x, scale.y, scale.z);
        // Semi-transparent so layer 1 shows through
        glColor4f(1.0f, 1.0f, 1.0f, 0.45f);
        background2->bindTexture();
        glBegin(GL_POLYGON);
            glTexCoord2f(x2Min, y2Max); glVertex3f(-w/h, -1.0, depth + 0.1f);
            glTexCoord2f(x2Max, y2Max); glVertex3f( w/h, -1.0, depth + 0.1f);
            glTexCoord2f(x2Max, y2Min); glVertex3f( w/h,  1.0, depth + 0.1f);
            glTexCoord2f(x2Min, y2Min); glVertex3f(-w/h,  1.0, depth + 0.1f);
        glEnd();
        glPopMatrix();
    }

    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);
}

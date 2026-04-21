#include "_hud.h"
#include <GL/glut.h>
#include <stdio.h>

_hud::_hud()
{
    health      = nullptr;
    score       = nullptr;
    kills       = nullptr;
    multiplier  = nullptr;
    bossHealth  = nullptr;
    lvl3        = nullptr;
    isPlayerDead = nullptr;
    isGameOver  = nullptr;
}

_hud::~_hud()
{
    //dtor
}

void _hud::init(int* hp, int* sc, int* kl, float* mp,
                int* bh, bool* l3, bool* dead, bool* over)
{
    health       = hp;
    score        = sc;
    kills        = kl;
    multiplier   = mp;
    bossHealth   = bh;
    lvl3         = l3;
    isPlayerDead = dead;
    isGameOver   = over;
}

void _hud::drawText(float x, float y, float z, const char* text)
{
    glRasterPos3f(x, y, z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void _hud::drawFilledRect(float x, float y, float w, float h)
{
    glBegin(GL_QUADS);
        glVertex3f(x,     y,     -11.9f);
        glVertex3f(x + w, y,     -11.9f);
        glVertex3f(x + w, y + h, -11.9f);
        glVertex3f(x,     y + h, -11.9f);
    glEnd();
}

void _hud::drawHealthBar()
{
    if(!health) return;

    // Dark background
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    drawFilledRect(-9.5f, 3.6f, 5.5f, 0.9f);

    // Label
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-9.3f, 3.7f, -11.9f, "HP:");

    // 3 hearts
    for(int i = 0; i < 3; i++)
    {
        float hx = -8.0f + i * 1.1f;
        if(i < *health)
        {
            // Full heart - red
            glColor3f(1.0f, 0.1f, 0.1f);
            drawFilledRect(hx, 3.7f, 0.8f, 0.6f);
            // Shine
            glColor3f(1.0f, 0.6f, 0.6f);
            drawFilledRect(hx + 0.05f, 4.15f, 0.3f, 0.1f);
        }
        else
        {
            // Empty heart - dark red
            glColor3f(0.25f, 0.0f, 0.0f);
            drawFilledRect(hx, 3.7f, 0.8f, 0.6f);
        }
    }
}

void _hud::drawScore()
{
    if(!score) return;

    // Dark background
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    drawFilledRect(-1.8f, 3.6f, 3.6f, 0.9f);

    glColor3f(1.0f, 1.0f, 0.0f);
    char txt[30];
    sprintf(txt, "SCORE: %d", *score);
    drawText(-1.6f, 3.7f, -11.9f, txt);
}

void _hud::drawKills()
{
    if(!kills) return;

    // Dark background
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    drawFilledRect(3.5f, 3.6f, 6.0f, 0.9f);

    glColor3f(0.0f, 1.0f, 0.5f);
    char txt[30];
    sprintf(txt, "KILLS: %d", *kills);
    drawText(3.7f, 3.7f, -11.9f, txt);
}

void _hud::drawMultiplier()
{
    if(!multiplier) return;

    // Dark background
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    drawFilledRect(3.5f, 2.6f, 6.0f, 0.9f);

    // Color based on multiplier
    if(*multiplier >= 4.0f)      glColor3f(1.0f, 0.0f, 1.0f);
    else if(*multiplier >= 3.0f) glColor3f(1.0f, 0.5f, 0.0f);
    else if(*multiplier >= 2.0f) glColor3f(1.0f, 1.0f, 0.0f);
    else                          glColor3f(1.0f, 1.0f, 1.0f);

    char txt[30];
    sprintf(txt, "X%.1f MULTIPLIER", *multiplier);
    drawText(3.7f, 2.7f, -11.9f, txt);

    // Fill bar background
    glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
    drawFilledRect(3.5f, 2.4f, 5.8f, 0.18f);

    // Fill bar
    float barW = (*multiplier / 5.0f) * 5.8f;
    if(barW > 5.8f) barW = 5.8f;

    if(*multiplier >= 4.0f)      glColor3f(1.0f, 0.0f, 1.0f);
    else if(*multiplier >= 3.0f) glColor3f(1.0f, 0.5f, 0.0f);
    else if(*multiplier >= 2.0f) glColor3f(1.0f, 1.0f, 0.0f);
    else                          glColor3f(0.0f, 0.8f, 1.0f);

    drawFilledRect(3.5f, 2.4f, barW, 0.18f);
}

void _hud::drawBossHealth()
{
    if(!bossHealth || !lvl3) return;
    if(!*lvl3) return;

    // Label
    glColor3f(1.0f, 0.3f, 0.3f);
    drawText(-0.8f, -4.6f, -11.9f, "BOSS");

    // Background bar
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    drawFilledRect(-4.5f, -4.35f, 9.0f, 0.5f);

    // Health fill
    float bw = ((float)*bossHealth / 10.0f) * 8.8f;
    if(bw < 0) bw = 0;
    float r = 1.0f - ((float)*bossHealth / 10.0f) * 0.3f;
    glColor3f(r, 0.1f, 0.1f);
    drawFilledRect(-4.4f, -4.25f, bw, 0.28f);
}

void _hud::drawGameOver()
{
    if(!isPlayerDead) return;
    if(!*isPlayerDead) return;

    // Dark overlay
    glColor4f(0.0f, 0.0f, 0.0f, 0.75f);
    drawFilledRect(-5.5f, -2.5f, 11.0f, 5.0f);

    // GAME OVER text
    glColor3f(1.0f, 0.1f, 0.1f);
    drawText(-1.8f, 1.5f, -11.9f, "GAME OVER");

    // Final score
    glColor3f(1.0f, 1.0f, 1.0f);
    if(score)
    {
        char sc[40];
        sprintf(sc, "Final Score: %d", *score);
        drawText(-1.5f, 0.6f, -11.9f, sc);
    }

    // Final kills
    if(kills)
    {
        char kl[40];
        sprintf(kl, "Total Kills: %d", *kills);
        drawText(-1.5f, -0.1f, -11.9f, kl);
    }

    glColor3f(0.5f, 0.5f, 0.5f);
    drawText(-2.0f, -1.0f, -11.9f, "Press ESC to exit");
}

void _hud::draw()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    drawHealthBar();
    drawScore();
    drawKills();
    drawMultiplier();
    drawBossHealth();
    drawGameOver();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

#include "_menu.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

static float uiTime = 0.0f;

_menu::_menu()
{
    currentState = LANDING;
    shouldQuit   = false;
    startGame    = false;
    restartGame  = false;

    landingTex = new _textureLoader();
    menuTex    = new _textureLoader();
    helpTex    = new _textureLoader();
    panelTex   = new _textureLoader();
}

_menu::~_menu()
{
    delete landingTex;
    delete menuTex;
    delete helpTex;
    delete panelTex;
}

void _menu::init()
{
    landingTex->loadTexture((char*)"images/spacebackground.png");
    menuTex->loadTexture((char*)"images/spacebackground.png");
    helpTex->loadTexture((char*)"images/spacebackground.png");
    panelTex->loadTexture((char*)"images/menubg.png");
}

void _menu::setupProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.777f, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void _menu::drawText(float x, float y, float z,
                     const char* text, void* font)
{
    glRasterPos3f(x, y, z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(font, text[i]);
}

void _menu::drawFilledRect(float x, float y,
                            float w, float h, float z)
{
    glBegin(GL_QUADS);
        glVertex3f(x,     y,     z);
        glVertex3f(x + w, y,     z);
        glVertex3f(x + w, y + h, z);
        glVertex3f(x,     y + h, z);
    glEnd();
}

void _menu::drawOutlineRect(float x, float y,
                             float w, float h, float z)
{
    glBegin(GL_LINE_LOOP);
        glVertex3f(x,     y,     z);
        glVertex3f(x + w, y,     z);
        glVertex3f(x + w, y + h, z);
        glVertex3f(x,     y + h, z);
    glEnd();
}

void _menu::drawFullScreenBg(GLuint tex)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-4.5f, -3.5f, -6.0f);
        glTexCoord2f(1, 1); glVertex3f( 4.5f, -3.5f, -6.0f);
        glTexCoord2f(1, 0); glVertex3f( 4.5f,  3.5f, -6.0f);
        glTexCoord2f(0, 0); glVertex3f(-4.5f,  3.5f, -6.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void _menu::drawPanel(float x, float y, float w, float h)
{
    float pulse = (sin(uiTime * 2.0f) + 1.0f) * 0.5f;

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // Dark glass body
    glColor4f(0.01f, 0.03f, 0.08f, 0.82f);
    drawFilledRect(x, y, w, h, -5.7f);

    // Soft inner blue layer
    glColor4f(0.0f, 0.35f, 0.55f, 0.18f);
    drawFilledRect(x + 0.12f, y + 0.12f,
                   w - 0.24f, h - 0.24f, -5.65f);

    // Outer glow border — pulses
    glLineWidth(4.0f);
    glColor4f(0.0f, 0.75f, 1.0f, 0.45f + pulse * 0.25f);
    drawOutlineRect(x, y, w, h, -5.55f);

    // Inner thin border
    glLineWidth(1.5f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.28f);
    drawOutlineRect(x + 0.15f, y + 0.15f,
                    w - 0.3f, h - 0.3f, -5.5f);

    glLineWidth(1.0f);
}

// ─────────────────────────────────────────────────────────────
//  LANDING
// ─────────────────────────────────────────────────────────────
void _menu::drawLanding()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setupProjection();

    glDisable(GL_LIGHTING);

    // Background
    drawFullScreenBg(landingTex->tex);

    // Dark overlay
    glDisable(GL_TEXTURE_2D);
    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    drawFilledRect(-4.5f, -3.5f, 9.0f, 7.0f, -5.9f);

    // Panel frame overlay
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, panelTex->tex);
    glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-4.5f, -3.5f, -5.8f);
        glTexCoord2f(1, 1); glVertex3f( 4.5f, -3.5f, -5.8f);
        glTexCoord2f(1, 0); glVertex3f( 4.5f,  3.5f, -5.8f);
        glTexCoord2f(0, 0); glVertex3f(-4.5f,  3.5f, -5.8f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    // Title shadow
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-2.22f, 1.52f, -5.7f,
             "SPACE INVADERS 178", GLUT_BITMAP_TIMES_ROMAN_24);

    // Title
    glColor3f(0.0f, 0.85f, 1.0f);
    drawText(-2.25f, 1.55f, -5.7f,
             "SPACE INVADERS 178", GLUT_BITMAP_TIMES_ROMAN_24);

    // Subtitle
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(-1.8f, 0.5f, -5.7f,
             "CSCI 178 - Game Development",
             GLUT_BITMAP_HELVETICA_18);

    // Prompt
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-1.8f, -0.5f, -5.7f,
             "Press ENTER or Click to Continue",
             GLUT_BITMAP_HELVETICA_18);

    glEnable(GL_LIGHTING);
}

// ─────────────────────────────────────────────────────────────
//  MENU
// ─────────────────────────────────────────────────────────────
void _menu::drawMenu()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setupProjection();

    glDisable(GL_LIGHTING);

    // Background
    drawFullScreenBg(menuTex->tex);

    // Dark overlay
    glDisable(GL_TEXTURE_2D);
    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    drawFilledRect(-4.5f, -3.5f, 9.0f, 7.0f, -5.9f);

    // Panel frame + dark box for text area
    drawPanel(-2.0f, -1.3f, 4.0f, 3.2f);

    // Title
    glColor3f(0.0f, 0.85f, 1.0f);
    drawText(-0.95f, 1.55f, -5.5f,
             "MAIN MENU", GLUT_BITMAP_TIMES_ROMAN_24);

    // Divider
    glColor4f(0.0f, 0.75f, 1.0f, 0.65f);
    glBegin(GL_LINES);
        glVertex3f(-2.5f, 1.2f, -5.5f);
        glVertex3f( 2.5f, 1.2f, -5.5f);
    glEnd();

    // Options
    glColor3f(0.0f, 1.0f, 0.65f);
    drawText(-0.85f, 0.55f, -5.5f,
             "N  START GAME", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.9f, 0.2f);
    drawText(-0.85f, -0.1f, -5.5f,
             "H  HOW TO PLAY", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.35f, 0.35f);
    drawText(-0.85f, -0.75f, -5.5f,
             "E  EXIT", GLUT_BITMAP_HELVETICA_18);

    glEnable(GL_LIGHTING);
}

// ─────────────────────────────────────────────────────────────
//  HELP
// ─────────────────────────────────────────────────────────────
void _menu::drawHelp()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setupProjection();

    glDisable(GL_LIGHTING);

    // Background
    drawFullScreenBg(helpTex->tex);

    // Dark overlay
    glDisable(GL_TEXTURE_2D);
    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    drawFilledRect(-4.5f, -3.5f, 9.0f, 7.0f, -5.9f);

    // Panel frame + dark box
    drawPanel(-4.0f, -3.2f, 8.0f, 6.4f);

    // Title
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(-1.0f, 2.8f, -5.5f,
             "HOW TO PLAY", GLUT_BITMAP_TIMES_ROMAN_24);

    glColor4f(0.0f, 0.75f, 1.0f, 0.65f);
    glBegin(GL_LINES);
        glVertex3f(-3.5f, 2.4f, -5.5f);
        glVertex3f( 3.5f, 2.4f, -5.5f);
    glEnd();

    glColor3f(0.0f, 0.85f, 1.0f);
    drawText(-3.5f, 2.0f, -5.5f,
             "CONTROLS:", GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.0f, 1.0f, 0.65f);
    drawText(-3.5f, 1.5f, -5.5f,
             "A / LEFT    -  Move ship left",
             GLUT_BITMAP_HELVETICA_18);
    drawText(-3.5f, 1.0f, -5.5f,
             "D / RIGHT   -  Move ship right",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.9f, 0.2f);
    drawText(-3.5f, 0.5f, -5.5f,
             "SPACE  -  Shoot laser",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.5f, 0.0f);
    drawText(-3.5f, 0.0f, -5.5f,
             "ESC    -  Pause game",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.0f, 0.85f, 1.0f);
    drawText(-3.5f, -0.5f, -5.5f,
             "GAMEPLAY:", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-3.5f, -1.0f, -5.5f,
             "Destroy enemies with asteroids or shoot them",
             GLUT_BITMAP_HELVETICA_18);
    drawText(-3.5f, -1.5f, -5.5f,
             "Score 10 = Level 2  |  Score 20 = Level 3 BOSS",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.35f, 0.35f);
    drawText(-3.5f, -2.0f, -5.5f,
             "3 lives - avoid enemies and boss lasers!",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.5f, 0.0f);
    drawText(-3.5f, -2.5f, -5.5f,
             "Kill streak boosts multiplier up to X5!",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.7f, 0.7f, 0.7f);
    drawText(-2.0f, -3.0f, -5.5f,
             "ESCAPE  -  Back to Menu",
             GLUT_BITMAP_HELVETICA_18);

    glEnable(GL_LIGHTING);
}

// ─────────────────────────────────────────────────────────────
//  PAUSE
// ─────────────────────────────────────────────────────────────
void _menu::drawPause()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // Dark overlay over game
    glColor4f(0.0f, 0.0f, 0.0f, 0.65f);
    glBegin(GL_QUADS);
        glVertex3f(-10.0f, -10.0f, -11.5f);
        glVertex3f( 10.0f, -10.0f, -11.5f);
        glVertex3f( 10.0f,  10.0f, -11.5f);
        glVertex3f(-10.0f,  10.0f, -11.5f);
    glEnd();

    // Dark glass box
    glColor4f(0.01f, 0.03f, 0.08f, 0.88f);
    drawFilledRect(-2.5f, -2.0f, 5.0f, 4.5f, -11.4f);

    // Pulsing border
    float pulse = (sin(uiTime * 2.0f) + 1.0f) * 0.5f;
    glLineWidth(3.0f);
    glColor4f(0.0f, 0.75f, 1.0f, 0.5f + pulse * 0.3f);
    drawOutlineRect(-2.5f, -2.0f, 5.0f, 4.5f, -11.3f);
    glLineWidth(1.0f);

    // Title
    glColor3f(1.0f, 0.1f, 0.1f);
    drawText(-0.55f, 1.8f, -11.2f,
             "PAUSED", GLUT_BITMAP_TIMES_ROMAN_24);

    glColor4f(0.0f, 0.75f, 1.0f, 0.65f);
    glBegin(GL_LINES);
        glVertex3f(-2.0f, 1.3f, -11.2f);
        glVertex3f( 2.0f, 1.3f, -11.2f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.3f);
    drawText(-1.2f, 0.7f, -11.2f,
             "ESCAPE  -  Resume", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.9f, 0.2f);
    drawText(-1.2f, 0.1f, -11.2f,
             "R       -  Restart", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.35f, 0.35f);
    drawText(-1.2f, -0.5f, -11.2f,
             "ENTER   -  Quit to Menu", GLUT_BITMAP_HELVETICA_18);

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_LIGHTING);
}

// ─────────────────────────────────────────────────────────────
//  DRAW
// ─────────────────────────────────────────────────────────────
void _menu::draw()
{
    uiTime += 0.016f;

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    switch(currentState)
    {
    case LANDING: drawLanding(); break;
    case MENU:    drawMenu();    break;
    case HELP:    drawHelp();    break;
    case PAUSE:   drawPause();   break;
    default: break;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
}

// ─────────────────────────────────────────────────────────────
//  HANDLE KEY
// ─────────────────────────────────────────────────────────────
bool _menu::handleKey(WPARAM wParam)
{
    startGame   = false;
    shouldQuit  = false;
    restartGame = false;

    switch(currentState)
    {
    case LANDING:
        if(wParam == VK_RETURN)
            currentState = MENU;
        break;

    case MENU:
        if(wParam == 'N')
        {
            currentState = GAME;
            startGame    = true;
        }
        else if(wParam == 'H')
            currentState = HELP;
        else if(wParam == 'E')
            shouldQuit = true;
        else if(wParam == VK_ESCAPE)
            currentState = LANDING;
        break;

    case HELP:
        if(wParam == VK_ESCAPE)
            currentState = MENU;
        break;

    case PAUSE:
        if(wParam == VK_ESCAPE)
            currentState = GAME;
        else if(wParam == 'R')
        {
            currentState = GAME;
            restartGame  = true;
        }
        else if(wParam == VK_RETURN)
            currentState = MENU;
        break;

    default: break;
    }

    return startGame;
}

// ─────────────────────────────────────────────────────────────
//  HANDLE CLICK
// ─────────────────────────────────────────────────────────────
bool _menu::handleClick(double mouseY)
{
    startGame = false;

    if(currentState == LANDING)
        currentState = MENU;
    else if(currentState == MENU)
    {
        if(mouseY >= 0.3 && mouseY <= 0.9)
        {
            currentState = GAME;
            startGame    = true;
        }
        else if(mouseY >= -0.2 && mouseY < 0.3)
            currentState = HELP;
        else if(mouseY >= -0.7 && mouseY < -0.2)
            shouldQuit = true;
    }

    return startGame;
}

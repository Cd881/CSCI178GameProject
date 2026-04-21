#include "_menu.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

_menu::_menu()
{
    currentState = LANDING;
    shouldQuit   = false;
    startGame    = false;
    restartGame  = false;

    landingTex = new _textureLoader();
    menuTex    = new _textureLoader();
    helpTex    = new _textureLoader();
}

_menu::~_menu()
{
    delete landingTex;
    delete menuTex;
    delete helpTex;
}

void _menu::init()
{
    // Each page gets its own space image
    landingTex->loadTexture((char*)"images/spacebackground.png");
    menuTex->loadTexture((char*)"images/space2.png");
    helpTex->loadTexture((char*)"images/space3.png");
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

// ─────────────────────────────────────────────────────────────
//  LANDING
// ─────────────────────────────────────────────────────────────
void _menu::drawLanding()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, landingTex->tex);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-10.0f, -6.0f, -11.9f);
        glTexCoord2f(1, 1); glVertex3f( 10.0f, -6.0f, -11.9f);
        glTexCoord2f(1, 0); glVertex3f( 10.0f,  6.0f, -11.9f);
        glTexCoord2f(0, 0); glVertex3f(-10.0f,  6.0f, -11.9f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // Dark overlay
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    drawFilledRect(-10.0f, -6.0f, 20.0f, 12.0f, -11.8f);

    // Title shadow
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-2.22f, 1.52f, -11.7f,
             "SPACE INVADERS 178", GLUT_BITMAP_TIMES_ROMAN_24);

    // Title
    glColor3f(0.0f, 0.8f, 1.0f);
    drawText(-2.25f, 1.55f, -11.7f,
             "SPACE INVADERS 178", GLUT_BITMAP_TIMES_ROMAN_24);

    // Subtitle
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(-1.8f, 0.7f, -11.7f,
             "CSCI 178 - Game Development", GLUT_BITMAP_HELVETICA_18);

    // Prompt
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-1.8f, -0.3f, -11.7f,
             "Press ENTER or Click to Continue",
             GLUT_BITMAP_HELVETICA_18);

    glEnable(GL_LIGHTING);
}

// ─────────────────────────────────────────────────────────────
//  MENU
// ─────────────────────────────────────────────────────────────
void _menu::drawMenu()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, menuTex->tex);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-10.0f, -6.0f, -11.9f);
        glTexCoord2f(1, 1); glVertex3f( 10.0f, -6.0f, -11.9f);
        glTexCoord2f(1, 0); glVertex3f( 10.0f,  6.0f, -11.9f);
        glTexCoord2f(0, 0); glVertex3f(-10.0f,  6.0f, -11.9f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // Dark overlay
    glColor4f(0.0f, 0.0f, 0.0f, 0.55f);
    drawFilledRect(-10.0f, -6.0f, 20.0f, 12.0f, -11.8f);

    // Menu box background
    glColor4f(0.0f, 0.0f, 0.2f, 0.85f);
    drawFilledRect(-3.5f, -2.5f, 7.0f, 5.0f, -11.7f);

    // Menu box border
    glColor3f(0.0f, 0.8f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-3.5f, -2.5f, -11.6f);
        glVertex3f( 3.5f, -2.5f, -11.6f);
        glVertex3f( 3.5f,  2.5f, -11.6f);
        glVertex3f(-3.5f,  2.5f, -11.6f);
    glEnd();
    glLineWidth(1.0f);

    // Title
    glColor3f(0.0f, 0.8f, 1.0f);
    drawText(-0.8f, 1.8f, -11.6f,
             "MAIN MENU", GLUT_BITMAP_TIMES_ROMAN_24);

    // Divider
    glBegin(GL_LINES);
        glVertex3f(-3.0f, 1.4f, -11.6f);
        glVertex3f( 3.0f, 1.4f, -11.6f);
    glEnd();

    // Options
    glColor3f(0.0f, 1.0f, 0.5f);
    drawText(-0.6f, 0.7f, -11.6f,
             "(N)  New Game", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(-0.6f, 0.0f, -11.6f,
             "(H)  How To Play", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.3f, 0.3f);
    drawText(-0.6f, -0.7f, -11.6f,
             "(E)  Exit", GLUT_BITMAP_HELVETICA_18);

    glEnable(GL_LIGHTING);
}

// ─────────────────────────────────────────────────────────────
//  HELP
// ─────────────────────────────────────────────────────────────
void _menu::drawHelp()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, helpTex->tex);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-10.0f, -6.0f, -11.9f);
        glTexCoord2f(1, 1); glVertex3f( 10.0f, -6.0f, -11.9f);
        glTexCoord2f(1, 0); glVertex3f( 10.0f,  6.0f, -11.9f);
        glTexCoord2f(0, 0); glVertex3f(-10.0f,  6.0f, -11.9f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // Dark overlay
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    drawFilledRect(-10.0f, -6.0f, 20.0f, 12.0f, -11.8f);

    // Help box
    glColor4f(0.0f, 0.0f, 0.2f, 0.85f);
    drawFilledRect(-5.5f, -3.8f, 11.0f, 7.6f, -11.7f);

    // Help box border
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-5.5f, -3.8f, -11.6f);
        glVertex3f( 5.5f, -3.8f, -11.6f);
        glVertex3f( 5.5f,  3.8f, -11.6f);
        glVertex3f(-5.5f,  3.8f, -11.6f);
    glEnd();
    glLineWidth(1.0f);

    // Title
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(-1.0f, 3.1f, -11.6f,
             "HOW TO PLAY", GLUT_BITMAP_TIMES_ROMAN_24);

    // Divider
    glBegin(GL_LINES);
        glVertex3f(-5.0f, 2.7f, -11.6f);
        glVertex3f( 5.0f, 2.7f, -11.6f);
    glEnd();

    // Controls section
    glColor3f(0.0f, 0.8f, 1.0f);
    drawText(-4.5f, 2.2f, -11.6f,
             "CONTROLS:", GLUT_BITMAP_HELVETICA_18);

    glColor3f(0.0f, 1.0f, 0.5f);
    drawText(-4.5f, 1.6f, -11.6f,
             "A / LEFT ARROW   -   Move ship left",
             GLUT_BITMAP_HELVETICA_18);
    drawText(-4.5f, 1.0f, -11.6f,
             "D / RIGHT ARROW  -   Move ship right",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(-4.5f, 0.4f, -11.6f,
             "SPACE   -   Shoot laser",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.5f, 0.0f);
    drawText(-4.5f, -0.2f, -11.6f,
             "ESC   -   Pause game",
             GLUT_BITMAP_HELVETICA_18);

    // Gameplay section
    glColor3f(0.0f, 0.8f, 1.0f);
    drawText(-4.5f, -0.9f, -11.6f,
             "GAMEPLAY:", GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-4.5f, -1.5f, -11.6f,
             "Destroy enemies with asteroids or shoot them",
             GLUT_BITMAP_HELVETICA_18);
    drawText(-4.5f, -2.1f, -11.6f,
             "Score 10 = Level 2  |  Score 20 = Level 3 (BOSS)",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.3f, 0.3f);
    drawText(-4.5f, -2.7f, -11.6f,
             "You have 3 lives - avoid enemies and boss lasers!",
             GLUT_BITMAP_HELVETICA_18);

    // Multiplier tip
    glColor3f(1.0f, 0.5f, 0.0f);
    drawText(-4.5f, -3.3f, -11.6f,
             "Kill streak boosts multiplier up to X5!",
             GLUT_BITMAP_HELVETICA_18);

    // Back prompt
    glColor3f(0.7f, 0.7f, 0.7f);
    drawText(-2.5f, -3.6f, -11.6f,
             "Press ESCAPE to return to Menu",
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
    drawFilledRect(-10.0f, -6.0f, 20.0f, 12.0f, -11.7f);

    // Popup box - taller to fit restart option
    glColor4f(0.0f, 0.0f, 0.15f, 0.95f);
    drawFilledRect(-3.0f, -2.5f, 6.0f, 5.0f, -11.6f);

    // Border
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-3.0f, -2.5f, -11.5f);
        glVertex3f( 3.0f, -2.5f, -11.5f);
        glVertex3f( 3.0f,  2.5f, -11.5f);
        glVertex3f(-3.0f,  2.5f, -11.5f);
    glEnd();
    glLineWidth(1.0f);

    // PAUSED title
    glColor3f(1.0f, 0.1f, 0.1f);
    drawText(-0.55f, 1.8f, -11.5f,
             "PAUSED", GLUT_BITMAP_TIMES_ROMAN_24);

    // Divider
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f(-2.5f, 1.4f, -11.5f);
        glVertex3f( 2.5f, 1.4f, -11.5f);
    glEnd();

    // Options
    glColor3f(0.0f, 1.0f, 0.3f);
    drawText(-1.5f, 0.8f, -11.5f,
             "ESCAPE  -  Resume Game",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(-1.5f, 0.1f, -11.5f,
             "R       -  Restart Game",
             GLUT_BITMAP_HELVETICA_18);

    glColor3f(1.0f, 0.3f, 0.3f);
    drawText(-1.5f, -0.6f, -11.5f,
             "ENTER   -  Quit to Menu",
             GLUT_BITMAP_HELVETICA_18);

    glEnable(GL_LIGHTING);
}

// ─────────────────────────────────────────────────────────────
//  DRAW — routes to correct page
// ─────────────────────────────────────────────────────────────
void _menu::draw()
{
    glDisable(GL_DEPTH_TEST);

    switch(currentState)
    {
    case LANDING: drawLanding(); break;
    case MENU:    drawMenu();    break;
    case HELP:    drawHelp();    break;
    case PAUSE:   drawPause();   break;
    default: break;
    }

    glEnable(GL_DEPTH_TEST);
}

// ─────────────────────────────────────────────────────────────
//  HANDLE KEY INPUT
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
        // ESC on menu goes back to landing
        else if(wParam == VK_ESCAPE)
            currentState = LANDING;
        break;

    case HELP:
        if(wParam == VK_ESCAPE)
            currentState = MENU;
        break;

    case PAUSE:
        if(wParam == VK_ESCAPE)
            currentState = GAME;   // resume
        else if(wParam == 'R')
        {
            currentState = GAME;
            restartGame  = true;   // signal scene to reset
        }
        else if(wParam == VK_RETURN)
            currentState = MENU;   // quit to menu
        break;

    default: break;
    }

    return startGame;
}

// ─────────────────────────────────────────────────────────────
//  HANDLE CLICK INPUT
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

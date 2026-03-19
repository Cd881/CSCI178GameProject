#include "_scene.h"

auto prevTime = chrono::steady_clock::now();

_scene::_scene()
{
    //ctor
}

_scene::~_scene()
{
    delete myLight;
    delete myKbMs;
    delete myPrlx;
    delete player;
    delete myMusic;
}

GLint _scene::initGL()
{
    glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Background color
    glClearDepth(1.0f); // depth test val
    glEnable(GL_DEPTH_TEST); // enable depth test
    glDepthFunc(GL_LEQUAL); // set depth test function to less than or equal

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //glEnable(GL_COLOR_MATERIAL);// wont need for 2d cause you will use textures instead of materials
    myLight->setLight(GL_LIGHT0);

    myPrlx->initPrlx("images/prlx.jpg");

    player->playerInit(4.0, 4.0, "images/players.png");

    myMusic->initSounds();
    //myMusic->playMusic("sounds/music1.mp3");

    for(int i = 0; i < 20; i++) {
        enemies[i].enemyInit(7, 2, "images/mon.png"); //TODO:: fix repeat read of file
        enemies[i].pos.x = (float)rand()/(float)(RAND_MAX)*10.0 - 4.0;
        float s = 0.8 + (float)(rand()%12)/10.0;
        enemies[i].scale.x = s;
        enemies[i].scale.y = s;
    }

    return true;
}

void _scene::reSize(GLint width, GLint height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height; // Calc aspect ratio
    glViewport(0, 0, width, height); // Adjust viewport

    glMatrixMode(GL_PROJECTION); // Init perspective projection
    glLoadIdentity(); // Init the matrix with identity matrix

    gluPerspective(45.0, aspectRatio, 0.1, 100.0); // Projection settings

    glMatrixMode(GL_MODELVIEW); // Init model and view matrix
    glLoadIdentity();

    dim.x = GetSystemMetrics(SM_CXSCREEN);
    dim.y = GetSystemMetrics(SM_CYSCREEN);
}

float _scene::deltaTime = 0; //init static var

void _scene::drawScene()
{
    auto currTime = chrono::steady_clock::now();
    chrono::duration<float> elapsed = currTime - prevTime;
    _scene::deltaTime = elapsed.count();
    prevTime = currTime;

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Clear buffers
    glLoadIdentity();

    glPushMatrix(); //background
        glScalef(13.3, 13.3, 1.0);
        myPrlx->drawBackground(dim.x, dim.y);
        myPrlx->scroll(true, myPrlx->RIGHT, 0.05 * deltaTime);
    glPopMatrix();

    player->playerActions(deltaTime);
    player->updateQuad();
    player->drawQuad();

    for(int i = 0; i < 20; i++) {
            if(hit->isRadialCol(enemies[i].pos, player->pos, 0.2, 0.3, 0.6)) {
                if (player->actionTrigger == player->RIGHTWALK && enemies[i].actionTrigger == enemies[i].LEFTWALK) {
                    enemies[i].actionTrigger = enemies[i].ROLRIGHT;
                }
                if (player->actionTrigger == player->LEFTWALK && enemies[i].actionTrigger == enemies[i].RIGHTWALK) {
                    enemies[i].actionTrigger = enemies[i].ROLLEFT;
                }
            }
            enemies[i].enemyActions(deltaTime);
            enemies[i].drawEnemy();
    }
}

int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
    case WM_KEYDOWN:
        myKbMs->wParam = wParam;
        myKbMs->keyPressed(player);
        break;
    case WM_KEYUP:
        player->actionTrigger = player->STAND;
        break;
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
        myKbMs->wParam = wParam;
        break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
        myKbMs->mouseEventUp();
        break;
    case WM_MOUSEMOVE:
        break;
    case WM_MOUSEWHEEL:
        break;
    }
}

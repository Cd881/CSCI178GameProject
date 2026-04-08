#include "_scene.h"

auto prevTime = chrono::steady_clock::now();

_scene::_scene()
{
    mouse.x = 0.0;
    mouse.y = 0.0;
    mouse.z = -6.0;

    score = 0;
    lvl2 = false;
    isGameOver = false;
}

_scene::~_scene()
{
    delete lights;
    delete bkgd;
    delete bkgd2;
    delete won;
    delete player;
    delete input;
    delete hit;
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

    bkgd->initPrlx("images/spacebackground.png");
    bkgd2->initPrlx("images/space2.png");
    won->initPrlx("images/won.png");

    asteroids[0].initAsteroid(rand()%16, "images/Asteroids.png");
    asteroids[0].altTex->loadTexture("images/Asteroids2.png");
    for(int i = 1; i < ASTEROID_SIZE; i++) {
        asteroids[i].myTex = asteroids[0].myTex;
        asteroids[i].initAsteroid(rand()%16, NULL);
    }

    enemies[0].enemyInit(4, 2, "images/newenms.png");
    for(int i = 1; i < ENMS_SIZE; i++) {
        enemies[i].myTex = enemies[0].myTex;
        enemies[i].enemyInit(4, 2, NULL);
    }

    player->playerInit(4,1,"images/ship.png");

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

    if(score < 10) {
        bkgd->drawBackground(dim.x, dim.y);
        bkgd->scroll(true, bkgd->UP, 0.1 * deltaTime);
    }else if(score < 25) {//level 2
        if(!lvl2) {//do once on level 2 start
            player->reset();
            for(int l = 0; l < ENMS_SIZE; l++) {
                    enemies[l].reset();
                    enemies[l].speed += 2.8; //make it harder
            }
            for(int l = 0; l < ASTEROID_SIZE; l++) {
                    asteroids[l].reset();
                    asteroids[l].myTex = asteroids[0].altTex;
            }
        }
        lvl2 = true;

        bkgd2->drawBackground(dim.x, dim.y);
        bkgd2->scroll(true, bkgd2->UP, 0.1 * deltaTime);
    } else {
        isGameOver = true;
        won->drawBackground(dim.x,dim.y);
    }

    if(!isGameOver) {
        player->playerActions(deltaTime);
        player->updateQuad();
        player->drawQuad();

        for(int i = 0; i < ASTEROID_SIZE; i++) {
            //could not find a good collision behavior for the asteroids
            //made them not reach the player before being hit by another asteroid
            /*for(int j = i+1; j < ASTEROID_SIZE; j++) {
                if(hit->isRadialCol(asteroids[i].pos, asteroids[j].pos, asteroids[i].scale.x, asteroids[j].scale.x, 0.01)) {
                // asteroid asteroid collision
                }
            }*/

            if(hit->isRadialCol(asteroids[i].pos, player->pos, asteroids[i].scale.x, 0.5, 0.008)) {//asteroid player collision
                //player hit asteroid
                if(!asteroids[i].isHit) {
                    asteroids[i].isHit = true;

                    vec2 normal;
                    normal.x = asteroids[i].pos.x - player->pos.x;
                    normal.y = asteroids[i].pos.y - player->pos.y;

                    float len = sqrt(normal.x*normal.x + normal.y*normal.y);//normalize
                    normal.x /= len;
                    normal.y /= len;

                    asteroids[i].dirVec = normal;
                    asteroids[i].hitDir = asteroids[i].HIT;
                    //old janky collision
                    /*if(player->actionTrigger == player->RIGHTWALK) {
                        if(asteroids[i].pos.y <= player->pos.y + 0.35)
                            asteroids[i].hitDir = asteroids[i].RIGHT;
                        else asteroids[i].hitDir = asteroids[i].UPRIGHT;
                    }
                    if(player->actionTrigger == player->LEFTWALK) {
                        if(asteroids[i].pos.y <= player->pos.y + 0.35)
                            asteroids[i].hitDir = asteroids[i].LEFT;
                        else asteroids[i].hitDir = asteroids[i].UPLEFT;
                    }
                    if(player->actionTrigger == player->STAND) asteroids[i].hitDir = asteroids[i].UP;*/
                }
            }

            for(int k = 0; k < ENMS_SIZE; k++) {
                if(hit->isRadialCol(enemies[k].pos, asteroids[i].pos, 0.2, asteroids[i].scale.x, 0.0000000001)) {
                    //asteroid enemy collision
                    if(asteroids[i].isHit && enemies[k].isEnmsLive) {
                        enemies[k].isEnmsLive = false;
                        enemies[k].actionTrigger = enemies[k].DEAD;
                        score++;
                    }
                }
                if(hit->isRadialCol(player->pos, enemies[k].pos, 0.3, 0.4, 0.002)) {
                    //player died reset level
                    if(enemies[k].isEnmsLive) {
                        if(lvl2) score = 10;
                        else score = 0;
                        player->reset();

                        for(int l = 0; l < ENMS_SIZE; l++) enemies[l].reset();
                        for(int l = 0; l < ASTEROID_SIZE; l++)asteroids[l].reset();
                    }
                }
            }
        }

        for(int i = 0; i < ENMS_SIZE; i ++) {
            enemies[i].enemyActions(deltaTime);
            enemies[i].drawEnemy();
        }

        for(int i = 0; i < ASTEROID_SIZE; i++) {
            asteroids[i].animate(deltaTime);
            asteroids[i].drawAsteroid();
        }
    }
}

void _scene::mouseMapping(int x, int y)
{
    GLint viewPort[4]; //for window
    GLdouble modelViewM[16]; //model and camera
    GLdouble projectionM[16]; //projection
    GLfloat winX,winY,winZ; // mouse clicks

    glGetDoublev(GL_MODELVIEW_MATRIX, modelViewM);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionM);
    glGetIntegerv(GL_VIEWPORT, viewPort);

    winX = (GLfloat)x;
    winY = (GLfloat)(viewPort[3] - y);

    glReadPixels(x,(int)winY,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&winZ);

    gluUnProject(winX,winY,winZ,modelViewM,projectionM,viewPort,&mouse.x,&mouse.y,&mouse.z);
}


int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
    case WM_KEYDOWN:
        input->wParam = wParam;
        input->keys[wParam] = true;
        input->keyPressed(player);
        break;
    case WM_KEYUP:
        input->wParam = wParam;
        input->keys[wParam] = false;
        input->keyUp(player);
        break;
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
        input->wParam = wParam;
        break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
        break;
    case WM_MOUSEMOVE:
        break;
    case WM_MOUSEWHEEL:
        break;
    }
}

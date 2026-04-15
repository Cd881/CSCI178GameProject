#include "_scene.h"

auto prevTime = chrono::steady_clock::now();

_scene::_scene()
{
    mouse.x = 0.0;
    mouse.y = 0.0;
    mouse.z = -6.0;

    timer = 0;

    score = 0;
    pause = false;
    lvl1 = false;
    lvl2 = false;
    lvl3 = false;
    isGameOver = false;
    frame = 0;
}

_scene::~_scene()
{
    delete lights;
    delete bkgd;
    delete bkgd2;
    delete bkgd3;
    delete won;
    delete player;
    delete input;
    delete hit;
    delete boss;
    delete cD;
    delete sound;
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
    bkgd3->initPrlx("images/space3.png");
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

    boss->bossInit(4, 3, "images/boss.png");

    player->playerInit(4,1,"images/ship.png");

    vec3 s;
    s.z = 1;
    s.x = s.y = 0.86;
    lvls[0].initPrlx("images/lvl1.png");
    lvls[0].depth = -2;
    lvls[0].scale = s;
    lvls[1].initPrlx("images/lvl2.png");
    lvls[1].depth = -2;
    lvls[1].scale = s;
    lvls[2].initPrlx("images/lvl3.png");
    lvls[2].depth = -2;
    lvls[2].scale = s;

    cD->countDownInit(1, 4, "images/countdown.png");

    sound->playMusic("sounds/music.mp3");

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

    if(!pause) {
        timer = 0;
    }

    //TODO:: ADD MAIN MENU HERE

    if(score < 10) {
        if(!lvl1) {//do once on the start of level one
            pause = true;
            timer += deltaTime;
            player->reset();

            bkgd->drawBackground(dim.x, dim.y);

            player->drawQuad();
            lvls[0].drawBackground(dim.x, dim.y);
            cD->drawCount();

            if(timer > 1.1) {
                cD->countIncrease();
                frame++;
                timer = 0;
            }
            if(frame >= 4) {
                lvl1 = true;
                pause = false;
                for(int i = 0; i < ENMS_SIZE; i++) {
                    enemies[i].reset();
                }
                for(int i = 0; i < ASTEROID_SIZE; i++) {
                    asteroids[i].reset();
                }
                frame = 0;
            }
        }

        bkgd->drawBackground(dim.x, dim.y);
        if(lvl1) bkgd->scroll(true, bkgd->UP, 0.1 * deltaTime);
        else bkgd->scroll(false, bkgd->UP, 0);
    }else if(score < 20) {//level 2
        if(!lvl2) {//do once on level 2 start
            pause = true;
            player->reset();
            timer += deltaTime;

            bkgd2->drawBackground(dim.x, dim.y);

            player->drawQuad();
            lvls[1].drawBackground(dim.x, dim.y);
            cD->drawCount();

            if(timer > 1.1) {
                cD->countIncrease();
                frame++;
                timer = 0;
            }
            if(frame >= 4) {
                lvl2 = true;
                pause = false;

                for(int l = 0; l < ENMS_SIZE; l++) {
                    enemies[l].reset();
                    enemies[l].speed += 2.2; //make it harder
                }
                for(int l = 0; l < ASTEROID_SIZE; l++) {
                    asteroids[l].reset();
                    asteroids[l].myTex = asteroids[0].altTex;
                }
                frame = 0;
            }
        }

        bkgd2->drawBackground(dim.x, dim.y);
        if(lvl2) bkgd2->scroll(true, bkgd2->UP, 0.1 * deltaTime);
        else bkgd2->scroll(false, bkgd->UP, 0);
    }else if(score < 30) {
        if(!lvl3) {//do once on level 3 start
            pause = true;
            player->reset();
            timer += deltaTime;

            bkgd3->drawBackground(dim.x, dim.y);

            player->drawQuad();
            lvls[2].drawBackground(dim.x, dim.y);
            cD->drawCount();

            if(timer > 1.1) {
                cD->countIncrease();
                frame++;
                timer = 0;
            }
            if(frame >= 4) {
                lvl3 = true;
                pause = false;

                boss->reset();

                for(int i = 0; i < ENMS_SIZE; i++) {
                    enemies[i].reset();
                }
                for(int i = 0; i < ASTEROID_SIZE; i++) {
                    asteroids[i].reset();
                }
                frame = 0;
            }
        }

        bkgd3->drawBackground(dim.x, dim.y);
        if(lvl3) bkgd3->scroll(true, bkgd2->UP, 0.1 * deltaTime);
        else bkgd3->scroll(false, bkgd->UP, 0);
    } else if(score > 34) {
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

                    if(rand()%2) sound->playSounds("sounds/bump1.mp3");
                    else sound->playSounds("sounds/bump2.mp3");
                }
            }

            for(int k = 0; k < ENMS_SIZE; k++) {
                if(!lvl3 && hit->isRadialCol(enemies[k].pos, asteroids[i].pos, 0.2, asteroids[i].scale.x, 0.0000000001)) {
                    //asteroid enemy collision
                    if(asteroids[i].isHit && enemies[k].isEnmsLive) {
                        enemies[k].isEnmsLive = false;
                        enemies[k].actionTrigger = enemies[k].DEAD;
                        score++;
                        //TODO:: add broken asteroid particles
                        asteroids[i].reset();
                    }
                }
                if(hit->isRadialCol(player->pos, enemies[k].pos, 0.3, 0.4, 0.002) || hit->isRadialCol(boss->pos, player->pos, 0.5, 0.5, 0.00001)) {
                    //player died reset level
                    if(enemies[k].isEnmsLive) {
                        if(lvl2) score = 10;
                        else if (lvl3) {
                            score = 20;
                            boss->reset();
                        } else score = 0;
                        player->reset();

                        for(int l = 0; l < ENMS_SIZE; l++) enemies[l].reset();
                        for(int l = 0; l < ASTEROID_SIZE; l++)asteroids[l].reset();
                    }
                }
            }
            if(lvl3) {
                if(boss->canDamage && hit->isRadialCol(boss->pos, asteroids[i].pos, 0.2, asteroids[i].scale.x, 0.0000000001)) {
                    if(asteroids[i].isHit) {
                        boss->health -= 1;
                        asteroids[i].reset();
                    }
                }
            }

            if(boss->health <= 0) boss->actionTrigger = boss->DEAD;
            if(!boss->isBossLive) score += 5;
        }

        if(!lvl3) {
            for(int i = 0; i < ENMS_SIZE; i ++) {
                if(pause){
                    enemies[i].actionTrigger = enemies[i].IDLE;
                }
                enemies[i].enemyActions(deltaTime);
                enemies[i].drawEnemy();
            }


            for(int i = 0; i < ASTEROID_SIZE; i++) {
                if(pause){
                    asteroids[i].hitDir = asteroids[i].IDLE;
                }
                asteroids[i].animate(deltaTime);
                asteroids[i].drawAsteroid();
            }
        } else {
            boss->bossActions(deltaTime, player->pos);
            boss->drawBoss();

            for(int i = 0; i < ASTEROID_SIZE - 5; i++) {
                asteroids[i].animate(deltaTime);
                asteroids[i].drawAsteroid();
            }
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

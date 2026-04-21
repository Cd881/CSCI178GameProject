#include "_scene.h"

auto prevTime = chrono::steady_clock::now();

_scene::_scene()
{
    mouse.x = 0.0f;
    mouse.y = 0.0f;
    mouse.z = -6.0f;

    timer           = 0.0f;
    score           = 0;
    pause           = false;
    lvl1            = false;
    lvl2            = false;
    lvl3            = false;
    isGameOver      = false;
    frame           = 0;
    playerHealth    = 3;
    kills           = 0;
    multiplier      = 1.0f;
    killStreak      = 0;
    streakTimer     = 0.0f;
    isPlayerDead    = false;
    shootSoundTimer = 0.0f;  // NEW

    lights = new _lightSettings();
    input  = new _inputs();
    bkgd   = new _parallax();
    bkgd2  = new _parallax();
    bkgd3  = new _parallax();
    won    = new _parallax();
    player = new _player();
    hit    = new _collisionCheck();
    boss   = new _boss();
    cD     = new _countdown();
    sound  = new _sounds();
    hud    = new _hud();
    menu   = new _menu();
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
    delete hud;
    delete menu;
}

GLint _scene::initGL()
{
    glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    menu->init();

    bkgd->initPrlx((char*)"images/spacebackground.png");
    bkgd2->initPrlx((char*)"images/space2.png");
    bkgd3->initPrlx((char*)"images/space3.png");
    won->initPrlx((char*)"images/won.png");

    asteroids[0].initAsteroid(rand() % 16, (char*)"images/Asteroids.png");
    asteroids[0].altTex->loadTexture((char*)"images/Asteroids2.png");
    for(int i = 1; i < ASTEROID_SIZE; i++)
    {
        asteroids[i].myTex = asteroids[0].myTex;
        asteroids[i].initAsteroid(rand() % 16, NULL);
    }

    enemies[0].enemyInit(4, 2, (char*)"images/newenms.png");
    for(int i = 1; i < ENMS_SIZE; i++)
    {
        enemies[i].myTex = enemies[0].myTex;
        enemies[i].enemyInit(4, 2, NULL);
    }

    boss->bossInit(4, 3, (char*)"images/boss.png");
    player->playerInit(4, 1, (char*)"images/ship.png");

    vec3 s;
    s.z = 1;
    s.x = s.y = 0.86f;

    lvls[0].initPrlx((char*)"images/lvl1.png");
    lvls[0].depth = -2;
    lvls[0].scale = s;

    lvls[1].initPrlx((char*)"images/lvl2.png");
    lvls[1].depth = -2;
    lvls[1].scale = s;

    lvls[2].initPrlx((char*)"images/lvl3.png");
    lvls[2].depth = -2;
    lvls[2].scale = s;

    cD->countDownInit(1, 4, (char*)"images/countdown.png");

    hud->init(&playerHealth, &score, &kills, &multiplier,
               &boss->health, &lvl3, &isPlayerDead, &isGameOver);

    // Init and start level 1 music
    sound->initSounds();
    sound->playMusic((char*)"sounds/music.mp3");

    return true;
}

void _scene::reSize(GLint width, GLint height)
{
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    dim.x = GetSystemMetrics(SM_CXSCREEN);
    dim.y = GetSystemMetrics(SM_CYSCREEN);
}

float _scene::deltaTime = 0;

void _scene::resetGame()
{
    score           = 0;
    pause           = false;
    lvl1            = false;
    lvl2            = false;
    lvl3            = false;
    isGameOver      = false;
    frame           = 0;
    playerHealth    = 3;
    kills           = 0;
    multiplier      = 1.0f;
    killStreak      = 0;
    streakTimer     = 0.0f;
    isPlayerDead    = false;
    timer           = 0.0f;
    shootSoundTimer = 0.0f;

    player->reset();
    boss->reset();
    cD->countDownInit(1, 4, (char*)"images/countdown.png");
    for(int i = 0; i < ENMS_SIZE; i++)    enemies[i].reset();
    for(int i = 0; i < ASTEROID_SIZE; i++) asteroids[i].reset();

    // Restart level 1 music
    sound->playMusic((char*)"sounds/music.mp3");
}

void _scene::playerTakeDamage()
{
    sound->playSounds((char*)"sounds/bump2.mp3");  // damage sound

    playerHealth--;
    killStreak  = 0;
    multiplier  = 1.0f;
    streakTimer = 0.0f;

    if(playerHealth <= 0)
    {
        isPlayerDead = true;
        isGameOver   = true;
        sound->stopMusic();
    }
    else
    {
        player->reset();
        for(int l = 0; l < ENMS_SIZE; l++)    enemies[l].reset();
        for(int l = 0; l < ASTEROID_SIZE; l++) asteroids[l].reset();
    }
}

void _scene::drawGame()
{
    streakTimer     += deltaTime;
    shootSoundTimer += deltaTime;

    if(streakTimer > 3.0f)
    {
        killStreak  = 0;
        multiplier  = 1.0f;
        streakTimer = 0.0f;
    }

    if(!pause) timer = 0;

    // ── LEVEL / BACKGROUND ───────────────────────────────────
    if(score < 10)
    {
        if(!lvl1)
        {
            pause = true;
            timer += deltaTime;
            player->reset();
            bkgd->drawBackground(dim.x, dim.y);
            player->drawQuad();
            lvls[0].drawBackground(dim.x, dim.y);
            cD->drawCount();
            if(timer > 1.1f) { cD->countIncrease(); frame++; timer = 0; }
            if(frame >= 4)
            {
                lvl1  = true;
                pause = false;
                for(int i = 0; i < ENMS_SIZE; i++)    enemies[i].reset();
                for(int i = 0; i < ASTEROID_SIZE; i++) asteroids[i].reset();
                frame = 0;
            }
        }
        bkgd->drawBackground(dim.x, dim.y);
        if(lvl1) bkgd->scroll(true,  bkgd->UP, 0.1f * deltaTime);
        else      bkgd->scroll(false, bkgd->UP, 0);
    }
    else if(score < 20)
    {
        if(!lvl2)
        {
            pause = true;
            player->reset();
            timer += deltaTime;
            bkgd2->drawBackground(dim.x, dim.y);
            player->drawQuad();
            lvls[1].drawBackground(dim.x, dim.y);
            cD->drawCount();
            if(timer > 1.1f) { cD->countIncrease(); frame++; timer = 0; }
            if(frame >= 4)
            {
                lvl2  = true;
                pause = false;
                for(int l = 0; l < ENMS_SIZE; l++)
                {
                    enemies[l].reset();
                    enemies[l].speed += 2.2f;
                }
                for(int l = 0; l < ASTEROID_SIZE; l++)
                {
                    asteroids[l].reset();
                    asteroids[l].myTex = asteroids[0].altTex;
                }
                frame = 0;

                // Level 2 music
                sound->playMusic((char*)"sounds/music1.mp3");
            }
        }
        bkgd2->drawBackground(dim.x, dim.y);
        if(lvl2) bkgd2->scroll(true,  bkgd2->UP, 0.1f * deltaTime);
        else      bkgd2->scroll(false, bkgd->UP,  0);
    }
    else if(score < 30)
    {
        if(!lvl3)
        {
            pause = true;
            player->reset();
            timer += deltaTime;
            bkgd3->drawBackground(dim.x, dim.y);
            player->drawQuad();
            lvls[2].drawBackground(dim.x, dim.y);
            cD->drawCount();
            if(timer > 1.1f) { cD->countIncrease(); frame++; timer = 0; }
            if(frame >= 4)
            {
                lvl3  = true;
                pause = false;
                boss->reset();
                for(int i = 0; i < ENMS_SIZE; i++)    enemies[i].reset();
                for(int i = 0; i < ASTEROID_SIZE; i++) asteroids[i].reset();
                frame = 0;

                // Level 3 boss music
                sound->playMusic((char*)"sounds/musicloud.mp3");
            }
        }
        bkgd3->drawBackground(dim.x, dim.y);
        if(lvl3) bkgd3->scroll(true,  bkgd2->UP, 0.1f * deltaTime);
        else      bkgd3->scroll(false, bkgd->UP,  0);
    }
    else if(score > 34)
    {
        isGameOver = true;
        won->drawBackground(dim.x, dim.y);
        sound->stopMusic();
    }

    // ── GAME LOGIC ───────────────────────────────────────────
    if(!isGameOver && menu->currentState != _menu::PAUSE)
    {
        player->playerActions(deltaTime);
        player->updateQuad();
        player->drawQuad();

        // Shoot sound
        if(input->keys[VK_SPACE] && shootSoundTimer > 0.1f)
        {
            sound->playSounds((char*)"sounds/laser1.mp3");
            shootSoundTimer = 0.0f;
        }

        // Boss fired sound
        if(boss->justFired)
        {
            sound->playSounds((char*)"sounds/laser2.mp3");
            boss->justFired = false;
        }

        for(int i = 0; i < 10; i++)
            player->bullets[i].drawLaser();

        // ── ASTEROID COLLISIONS ──────────────────────────────
        for(int i = 0; i < ASTEROID_SIZE; i++)
        {
            if(hit->isRadialCol(asteroids[i].pos, player->pos,
                                 asteroids[i].scale.x, 0.5, 0.008))
            {
                if(!asteroids[i].isHit)
                {
                    asteroids[i].isHit = true;
                    vec2 normal;
                    normal.x = asteroids[i].pos.x - player->pos.x;
                    normal.y = asteroids[i].pos.y - player->pos.y;
                    float len = sqrt(normal.x*normal.x + normal.y*normal.y);
                    normal.x /= len;
                    normal.y /= len;
                    asteroids[i].dirVec = normal;
                    asteroids[i].hitDir = asteroids[i].HIT;
                    playerTakeDamage();
                }
            }

            for(int k = 0; k < ENMS_SIZE; k++)
            {
                // Asteroid kills enemy
                if(!lvl3 && hit->isRadialCol(enemies[k].pos, asteroids[i].pos,
                                              0.2, asteroids[i].scale.x, 0.0000000001))
                {
                    if(asteroids[i].isHit && enemies[k].isEnmsLive)
                    {
                        enemies[k].isEnmsLive    = false;
                        enemies[k].actionTrigger = enemies[k].DEAD;
                        asteroids[i].reset();
                        sound->playSounds((char*)"sounds/bump1.mp3"); // enemy death
                        kills++;
                        killStreak++;
                        streakTimer = 0.0f;
                        score += (int)(1 * multiplier);
                        if(killStreak >= 10)     multiplier = 5.0f;
                        else if(killStreak >= 7) multiplier = 4.0f;
                        else if(killStreak >= 5) multiplier = 3.0f;
                        else if(killStreak >= 3) multiplier = 2.0f;
                        else                     multiplier = 1.0f;
                    }
                }

                // Enemy hits player
                if(hit->isRadialCol(player->pos, enemies[k].pos, 0.3, 0.4, 0.002))
                {
                    if(enemies[k].isEnmsLive)
                    {
                        playerTakeDamage();
                        if(!isPlayerDead)
                        {
                            if(lvl2)      score = 10;
                            else if(lvl3) { score = 20; boss->reset(); }
                            else           score = 0;
                        }
                    }
                }

                // Boss hits player
                if(hit->isRadialCol(boss->pos, player->pos, 0.5, 0.5, 0.00001))
                {
                    playerTakeDamage();
                    if(!isPlayerDead && lvl3) { score = 20; boss->reset(); }
                }
            }

            // Boss vs asteroid
            if(lvl3 && boss->canDamage &&
               hit->isRadialCol(boss->pos, asteroids[i].pos,
                                0.2, asteroids[i].scale.x, 0.0000000001))
            {
                if(asteroids[i].isHit)
                {
                    boss->health -= 1;
                    asteroids[i].reset();
                }
            }

            if(boss->health <= 0) boss->actionTrigger = boss->DEAD;
            if(!boss->isBossLive) score += 5;
        }

        // ── PLAYER BULLET COLLISIONS ─────────────────────────
        for(int b = 0; b < 10; b++)
        {
            if(!player->bullets[b].isLive) continue;

            // Bullet kills enemy
            for(int k = 0; k < ENMS_SIZE; k++)
            {
                if(hit->isRadialCol(player->bullets[b].pos,
                                    enemies[k].pos, 0.15, 0.4, 0.001))
                {
                    if(enemies[k].isEnmsLive)
                    {
                        enemies[k].isEnmsLive    = false;
                        enemies[k].actionTrigger = enemies[k].DEAD;
                        player->bullets[b].isLive        = false;
                        player->bullets[b].actionTrigger = _bullets::IDLE;
                        sound->playSounds((char*)"sounds/bump1.mp3"); // enemy death
                        kills++;
                        killStreak++;
                        streakTimer = 0.0f;
                        score += (int)(1 * multiplier);
                        if(killStreak >= 10)     multiplier = 5.0f;
                        else if(killStreak >= 7) multiplier = 4.0f;
                        else if(killStreak >= 5) multiplier = 3.0f;
                        else if(killStreak >= 3) multiplier = 2.0f;
                        else                     multiplier = 1.0f;
                    }
                }
            }

            // Bullet hits asteroid
            for(int a = 0; a < ASTEROID_SIZE; a++)
            {
                if(hit->isRadialCol(player->bullets[b].pos,
                                    asteroids[a].pos, 0.15,
                                    asteroids[a].scale.x, 0.001))
                {
                    asteroids[a].isHit               = true;
                    player->bullets[b].isLive        = false;
                    player->bullets[b].actionTrigger = _bullets::IDLE;
                }
            }

            // Bullet hits boss
            if(lvl3 && hit->isRadialCol(player->bullets[b].pos,
                                         boss->pos, 0.15, 0.5, 0.001))
            {
                boss->health -= 1;
                player->bullets[b].isLive        = false;
                player->bullets[b].actionTrigger = _bullets::IDLE;
                sound->playSounds((char*)"sounds/bump1.mp3"); // boss hit
            }
        }

        // ── BOSS LASER vs PLAYER ─────────────────────────────
        if(lvl3)
        {
            for(int b = 0; b < 10; b++)
            {
                if(boss->lasers[b].isLive)
                {
                    if(hit->isRadialCol(boss->lasers[b].pos,
                                        player->pos, 0.15, 0.4, 0.001))
                    {
                        boss->lasers[b].isLive        = false;
                        boss->lasers[b].actionTrigger = _bullets::IDLE;
                        playerTakeDamage();
                        if(!isPlayerDead) { score = 20; boss->reset(); }
                    }
                }
            }
        }

        // ── DRAW ─────────────────────────────────────────────
        if(!lvl3)
        {
            for(int i = 0; i < ENMS_SIZE; i++)
            {
                if(pause) enemies[i].actionTrigger = enemies[i].IDLE;
                enemies[i].enemyActions(deltaTime);
                enemies[i].drawEnemy();
            }
            for(int i = 0; i < ASTEROID_SIZE; i++)
            {
                if(pause) asteroids[i].hitDir = asteroids[i].IDLE;
                asteroids[i].animate(deltaTime);
                asteroids[i].drawAsteroid();
            }
        }
        else
        {
            boss->bossActions(deltaTime, player->pos);
            boss->drawBoss();
            for(int i = 0; i < ASTEROID_SIZE - 5; i++)
            {
                asteroids[i].animate(deltaTime);
                asteroids[i].drawAsteroid();
            }
        }
    }
    else if(isGameOver)
    {
        // Still draw everything frozen when game over
        player->drawQuad();
        if(!lvl3)
        {
            for(int i = 0; i < ENMS_SIZE; i++)  enemies[i].drawEnemy();
            for(int i = 0; i < ASTEROID_SIZE; i++) asteroids[i].drawAsteroid();
        }
        else
        {
            boss->drawBoss();
        }
    }

    hud->draw();
}

void _scene::drawScene()
{
    auto currTime = chrono::steady_clock::now();
    chrono::duration<float> elapsed = currTime - prevTime;
    _scene::deltaTime = elapsed.count();
    prevTime = currTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if(menu->currentState == _menu::GAME ||
       menu->currentState == _menu::PAUSE)
    {
        drawGame();
    }

    if(menu->currentState != _menu::GAME)
        menu->draw();
}

void _scene::mouseMapping(int x, int y)
{
    GLint    viewPort[4];
    GLdouble modelViewM[16];
    GLdouble projectionM[16];
    GLfloat  winX, winY, winZ;

    glGetDoublev(GL_MODELVIEW_MATRIX,  modelViewM);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionM);
    glGetIntegerv(GL_VIEWPORT,         viewPort);

    winX = (GLfloat)x;
    winY = (GLfloat)(viewPort[3] - y);

    glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, modelViewM, projectionM, viewPort,
                 &mouse.x, &mouse.y, &mouse.z);
}

int _scene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_KEYDOWN:
        if(menu->currentState != _menu::GAME)
        {
            bool wasPaused = (menu->currentState == _menu::PAUSE);
            bool started   = menu->handleKey(wParam);

            if(started)
            {
                resetGame();
                sound->playMusic((char*)"sounds/music.mp3");
            }
            if(menu->restartGame)
            {
                resetGame();
                sound->playMusic((char*)"sounds/music.mp3");
            }
            if(menu->shouldQuit) PostQuitMessage(0);

            // Resume sound when unpausing
            if(wasPaused && menu->currentState == _menu::GAME)
                sound->resumeAll();
        }
        else
        {
            if(wParam == VK_ESCAPE)
            {
                menu->currentState = _menu::PAUSE;
                sound->pauseAll();  // pause music on pause
            }
            else
            {
                input->wParam = wParam;
                input->keys[wParam] = true;
                input->keyPressed(player);
            }
        }
        break;

    case WM_KEYUP:
        if(menu->currentState == _menu::GAME)
        {
            input->wParam = wParam;
            input->keys[wParam] = false;
            input->keyUp(player);
        }
        break;

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
        mouseMapping(LOWORD(lParam), HIWORD(lParam));
        if(menu->currentState != _menu::GAME)
        {
            bool started = menu->handleClick(mouse.y);
            if(started)
            {
                resetGame();
                sound->playMusic((char*)"sounds/music.mp3");
            }
            if(menu->shouldQuit) PostQuitMessage(0);
        }
        break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
        break;
    case WM_MOUSEMOVE:
        break;
    case WM_MOUSEWHEEL:
        break;
    }
    return 0;
}

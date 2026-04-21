#ifndef _SCENE_H
#define _SCENE_H
#include <_common.h>
#include <_lightSettings.h>
#include <_model.h>
#include <_inputs.h>
#include <_modelVBO.h>
#include <_parallax.h>
#include <_quad.h>
#include <_player.h>
#include <_sounds.h>
#include <_enemy.h>
#include <_collisionCheck.h>
#include <_bullets.h>
#include <_asteroid.h>
#include <_countdown.h>
#include <_boss.h>
#include <_hud.h>
#include <_menu.h>

class _scene
{
public:
    _scene();
    virtual ~_scene();
    GLint initGL();
    void reSize(GLint, GLint);
    void drawScene();
    void mouseMapping(int, int);
    int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static float deltaTime;

    _lightSettings*  lights;
    _inputs*         input;
    _parallax*       bkgd;
    _parallax*       bkgd2;
    _parallax*       bkgd3;
    _parallax*       won;
    _player*         player;
    _collisionCheck* hit;
    _boss*           boss;
    _countdown*      cD;
    _sounds*         sound;
    _hud*            hud;
    _menu*           menu;

    int frame;
    _parallax lvls[3];
    const static int ASTEROID_SIZE = 15;
    const static int ENMS_SIZE = 5;
    _asteroid asteroids[ASTEROID_SIZE];
    _enemy    enemies[ENMS_SIZE];

    int   score;
    bool  lvl1, lvl2, lvl3, isGameOver, pause;
    float timer;
    vec3  mouse;
    vec2  dim;

    int   playerHealth;
    int   kills;
    float multiplier;
    int   killStreak;
    float streakTimer;
    bool  isPlayerDead;
    float shootSoundTimer;  // NEW

    void playerTakeDamage();
    void resetGame();

protected:
private:
    void drawGame();
};

#endif // _SCENE_H

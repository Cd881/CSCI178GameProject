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

class _scene
{
    public:
        _scene();
        virtual ~_scene();

        GLint initGL(); // Init openGL contents

        void reSize(GLint, GLint); // Handles window resizing
        void drawScene(); // Render the final scene

        void mouseMapping(int,int);

        int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        static float deltaTime;

        _lightSettings *lights = new _lightSettings();
        _inputs *input = new _inputs();
        _parallax *bkgd = new _parallax();
        _parallax *bkgd2 = new _parallax();
        _parallax *bkgd3 = new _parallax();
        _parallax *won = new _parallax();
        _player *player = new _player();
        _collisionCheck *hit = new _collisionCheck();
        _boss *boss = new _boss();
        _countdown *cD = new _countdown();
        _sounds *sound = new _sounds();

        int frame; //to keep track of frames for countdown
        _parallax lvls[3];

        const static int ASTEROID_SIZE = 15;
        const static int ENMS_SIZE = 5;
        _asteroid asteroids[ASTEROID_SIZE];
        _enemy enemies[ENMS_SIZE];

        int score;
        bool lvl1, lvl2, lvl3, isGameOver, pause;
        float timer;

        vec3 mouse; //to keep track of the mouse loc
        vec2 dim; //window size

    protected:

    private:
};

#endif // _SCENE_H

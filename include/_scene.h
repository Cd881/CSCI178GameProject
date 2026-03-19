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

class _scene
{
    public:
        _scene();
        virtual ~_scene();

        GLint initGL(); // Init openGL contents

        void reSize(GLint, GLint); // Handles window resizing
        void drawScene(); // Render the final scene

        int winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        static float deltaTime;

        _lightSettings *myLight = new _lightSettings();
        _inputs *myKbMs = new _inputs();
        _parallax *myPrlx = new _parallax();
        _player *player = new _player();
        _sounds *myMusic = new _sounds();
        _collisionCheck *hit = new _collisionCheck();

        _enemy enemies[20];

        vec2 dim;

    protected:

    private:
};

#endif // _SCENE_H

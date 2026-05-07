#ifndef _MENU_H
#define _MENU_H
#include <_common.h>
#include <_textureLoader.h>

class _menu
{
    public:
        _menu();
        virtual ~_menu();

        enum GameState { LANDING, MENU, GAME, HELP, PAUSE };
        GameState currentState;

        void init();
        void draw();
        void drawLanding();
        void drawMenu();
        void drawHelp();
        void drawPause();

        bool handleKey(WPARAM wParam);
        bool handleClick(double mouseY);

        bool shouldQuit;
        bool startGame;
        bool restartGame;

    private:
        _textureLoader* landingTex;
        _textureLoader* menuTex;
        _textureLoader* helpTex;
        _textureLoader* panelTex;

        void setupProjection();
        void drawFullScreenBg(GLuint tex);
        void drawText(float x, float y, float z,
                      const char* text, void* font);
        void drawFilledRect(float x, float y,
                            float w, float h, float z);
        void drawOutlineRect(float x, float y,
                             float w, float h, float z);
        void drawPanel(float x, float y, float w, float h);
};

#endif // _MENU_H

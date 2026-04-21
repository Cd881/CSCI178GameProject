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

        // Input handling — returns true if state changed to GAME
        bool handleKey(WPARAM wParam);
        bool handleClick(double mouseY);

        bool shouldQuit;    // set true when E/ESC pressed on menu
        bool startGame;     // set true when N pressed
        bool restartGame;   // set true to restart

    private:
        _textureLoader* landingTex;
        _textureLoader* menuTex;
        _textureLoader* helpTex;

        void drawText(float x, float y, float z,
                      const char* text, void* font);
        void drawFilledRect(float x, float y, float w, float h, float z);
};

#endif // _MENU_H

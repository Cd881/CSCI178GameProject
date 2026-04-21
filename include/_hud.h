#ifndef _HUD_H
#define _HUD_H
#include <_common.h>

class _hud
{
    public:
        _hud();
        virtual ~_hud();

        // Data the HUD needs to display
        int*   health;       // pointer to player health
        int*   score;        // pointer to scene score
        int*   kills;        // pointer to kill count
        float* multiplier;   // pointer to multiplier
        int*   bossHealth;   // pointer to boss health
        bool*  lvl3;         // pointer to lvl3 flag
        bool*  isPlayerDead; // pointer to dead flag
        bool*  isGameOver;   // pointer to game over flag

        void init(int* hp, int* sc, int* kl, float* mp,
                  int* bh, bool* l3, bool* dead, bool* over);

        void draw();

    private:
        void drawText(float x, float y, float z, const char* text);
        void drawFilledRect(float x, float y, float w, float h);
        void drawHealthBar();
        void drawScore();
        void drawKills();
        void drawMultiplier();
        void drawBossHealth();
        void drawGameOver();
};

#endif // _HUD_H

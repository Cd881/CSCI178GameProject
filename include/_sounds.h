#ifndef _SOUNDS_H
#define _SOUNDS_H
#include <_common.h>

class _sounds
{
    public:
        _sounds();
        virtual ~_sounds();

        bool isInitialized;

        void initSounds();
        void playMusic(char* fileName);
        void stopMusic();
        void playSounds(char* fileName);
        void pauseAll();
        void resumeAll();

    protected:
    private:
};

#endif // _SOUNDS_H

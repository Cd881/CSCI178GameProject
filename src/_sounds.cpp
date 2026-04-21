#include "_sounds.h"
#include <iostream>
using namespace std;

_sounds::_sounds()
{
    isInitialized = false;
}

_sounds::~_sounds()
{
    // disabled
}

void _sounds::initSounds()
{
    cout << "Sound disabled" << endl;
}

void _sounds::playMusic(char* fileName)
{
    // disabled
}

void _sounds::stopMusic()
{
    // disabled
}

void _sounds::playSounds(char* fileName)
{
    // disabled
}

void _sounds::pauseAll()
{
    // disabled
}

void _sounds::resumeAll()
{
    // disabled
}

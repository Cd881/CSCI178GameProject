#include "_sounds.h"

_sounds::_sounds()
{
    //ctor
}

_sounds::~_sounds()
{
    //dtor
    sndEng->drop();
    delete sndEng;
}

void _sounds::playMusic(char* filename)
{
    sndEng->play2D(filename, true);
}

void _sounds::playSounds(char* filename)
{
    sndEng->play2D(filename, false, false);
}

void _sounds::pauseSound(char* filename)
{
    sndEng->play2D(filename, true, false);
}

void _sounds::initSounds()
{
    if(!sndEng) cout << "ERROR: Sound Engine did not start\n";
}

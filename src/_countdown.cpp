#include "_countdown.h"

_countdown::_countdown()
{
    //ctor
    scale.x = 0.2;
    scale.y = 0.2;
    scale.z = 1.0;
}

_countdown::~_countdown()
{
    //dtor
}

void _countdown::countDownInit(int x, int y, char* filename)
{
    initQuad(filename);

    xFrames = x;
    yFrames = y;

    xMin = 0.0;
    xMax = 1.0/(float)xFrames;
    yMin = 0.0;
    yMax = 1.0/(float)yFrames;

    pos.y = -0.4;
    pos.x = 0;
    pos.z = -1.9;
}

void _countdown::countIncrease()
{
    yMin += 1.0/(float)yFrames;
    yMax += 1.0/(float)yFrames;
}

void _countdown::countReset()
{
    xMin = 0.0;
    xMax = 1.0/(float)xFrames;
    yMin = 0.0;
    yMax = 1.0/(float)yFrames;
}

void _countdown::drawCount()
{
    updateQuad();
    drawQuad();
}

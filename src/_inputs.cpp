#include "_inputs.h"

_inputs::_inputs()
{
    //ctor
    isRotation = false;
    isTranslate = false;

    isPressedLeft = false;
    isPressedRight = false;
    for(int i = 0; i < 256; i++)
        keys[i] = false;
}

_inputs::~_inputs()
{
    //dtor
}
void _inputs::keyPressed(_model *mdl)
{
    //cout << wParam << endl;
    switch(wParam){
    case VK_LEFT:
        mdl->rotation.y += 1.0;
        break;
    case VK_RIGHT:
        mdl->rotation.y -= 1.0;
        break;
    case VK_UP:
        mdl->rotation.x += 1.0;
        break;
    case VK_DOWN:
        mdl->rotation.x -= 1.0;
        break;
    }
}

void _inputs::keyUP()
{
    switch(wParam){
    default:
        break;
    }
}

void _inputs::mouseEventDown(_model *mdl,double x, double y)
{
    prevMx = x;
    prevMy = y;

    switch(wParam){
    case MK_LBUTTON:
        isRotation = true;
        break;
    case MK_RBUTTON:
        isTranslate = true;
        break;
    case MK_MBUTTON:
        break;
    default:
        break;
    }
}

void _inputs::mouseEventUp()
{
    isRotation = false;
    isTranslate = false;
}

void _inputs::mouseMove(_model *mdl,double x, double y)
{
    if(isRotation) {
        mdl->rotation.x += (y - prevMy)/3.0;
        mdl->rotation.y += (x - prevMx)/3.0;
    }
    if(isTranslate){
        mdl->pos.x += (x - prevMx)/100.0;
        mdl->pos.y -= (y - prevMy)/100.0;
    }


    prevMx = x;
    prevMy = y;
}

void _inputs::mouseWheel(_model *mdl,double delta)
{
    mdl->pos.z += delta/100.0;
}

void _inputs::keyPressed(_modelVBO* mdlv)
{
    switch(wParam){
    case 65:
        mdlv->rot.y -= 1.0;
        break;
    case 68:
        mdlv->rot.y += 1.0;
        break;
    case 87:
        mdlv->rot.x -= 1.0;
        break;
    case 83:
        mdlv->rot.x += 1.0;
        break;
    }
}

void _inputs::mouseEventDown(_modelVBO* mdlv, double x, double y)
{
    prevMx = x;
    prevMy = y;

    switch(wParam){
    case MK_LBUTTON:
        isRotation = true;
        break;
    case MK_RBUTTON:
        isTranslate = true;
        break;
    case MK_MBUTTON:
        break;
    default:
        break;
    }
}

void _inputs::mouseMove(_modelVBO* mdlv, double x, double y)
{
    if(isRotation) {
        mdlv->rot.x += (x - prevMx)/3.0;
        mdlv->rot.y += (y - prevMy)/3.0;
    }
    if(isTranslate){
        mdlv->pos.x += (x - prevMx)/100.0;
        mdlv->pos.y += (y - prevMy)/100.0;
    }


    prevMx = x;
    prevMy = y;
}

void _inputs::mouseWheel(_modelVBO* mdlv, double delta)
{
    mdlv->pos.z += delta/100.0;
}

void _inputs::keyPressed(_player* p)
{
    if(keys[65] || keys[37]) p->actionTrigger = p->LEFTWALK;//a or left
    if(keys[68] || keys[39]) p->actionTrigger = p->RIGHTWALK;//d or right
}

void _inputs::keyUp(_player *p)
{
    if(!keys[65] || !keys[68] || !keys[37] || !keys[39]) p->actionTrigger = p->STAND;
}

#include "_parallax.h"

_parallax::_parallax()
{
    xMax = 1.0;
    xMin = 0.0;
    yMax = 1.0;
    yMin = 0.0;
}

_parallax::~_parallax()
{
    delete background;
}

void _parallax::initPrlx(char* filename)
{
    background->loadTexture(filename);
}

void _parallax::scroll(bool isAuto, int dir, float speed)
{
    if(isAuto) {
        switch(dir){
        case LEFT:
            xMin -= speed;
            xMax -= speed;
            break;
        case RIGHT:
            xMin += speed;
            xMax += speed;
            break;
        case UP:
            yMin -= speed;
            yMax -= speed;
            break;
        case DOWN:
            yMin += speed;
            yMax += speed;
            break;
        default:
            break;
        }
    }
}

void _parallax::drawBackground(float w, float h)
{
    glColor3f(1.0, 1.0, 1.0);
    background->bindTexture();

    glDisable(GL_LIGHTING);
    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMax);
        glVertex3f(-w/h, -1.0, -30.0);

        glTexCoord2f(xMax, yMax);
        glVertex3f(w/h, -1.0, -30.0);

        glTexCoord2f(xMax, yMin);
        glVertex3f(w/h, 1.0, -30.0);

        glTexCoord2f(xMin, yMin);
        glVertex3f(-w/h, 1.0, -30.0);
    glEnd();
    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);
}

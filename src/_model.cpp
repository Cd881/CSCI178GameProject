#include "_model.h"

_model::_model()
{
    //ctor
}

_model::~_model()
{
    delete myImage;
}

void _model::initModel(char *filename)
{
    rotation.x = 0.0, rotation.y = 0.0, rotation.z = 0.0;
    pos.x = 0.0, pos.y = 0.0, pos.z = -8.0;
    scale.x = scale.y = scale.z = 1.0;

    myImage->loadTexture(filename);
}

void _model::drawModel()
{
    glPushMatrix();
        glColor3f(0.0,0.5,1.0); // Set base color
        glTranslatef(pos.x, pos.y, pos.z); // Place the object
        glRotatef(rotation.x, 1.0, 0.0, 0.0); // Rotation around x
        glRotatef(rotation.y, 0.0, 1.0, 0.0); // Rotation around y
        glRotatef(rotation.z, 0.0, 0.0, 1.0); // Rotation around z
        glScalef(scale.x, scale.y, scale.z); // Resize the object

        myImage->bindTexture();
        glutSolidTeapot(1.5);
    glPopMatrix();
}

#include "_modelVBO.h"

_modelVBO::_modelVBO()
{
    rot.x = rot.y = rot.z = 0.0;
    scale.x = scale.y = scale.z = 1.0;
    pos.x = 0.0;
    pos.y = 0.0;
    pos.z = -4.0;
}

_modelVBO::~_modelVBO()
{
    delete myImage;
}

void _modelVBO::drawModel()
{
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);

        glTranslatef(pos.x, pos.y, pos.z);

        glRotatef(rot.x, 1.0, 0.0, 0.0);
        glRotatef(rot.y, 0.0, 1.0, 0.0);
        glRotatef(rot.z, 0.0, 0.0, 1.0);

        glScalef(scale.x, scale.y, scale.z);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
        glVertexPointer(3, GL_FLOAT, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vboNorms);
        glNormalPointer(GL_FLOAT, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

        myImage->bindTexture();

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    glPopMatrix();
}

void _modelVBO::initModel(char *filename)
{
    // Set-up VBO
    glGenBuffers(1, &vboVerts);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &vboNorms);
    glBindBuffer(GL_ARRAY_BUFFER, vboNorms);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

    // Set-up faces
    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    myImage->loadTexture(filename);
}

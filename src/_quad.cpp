#include "_quad.h"

_quad::_quad()
{
    //ctor
    rot.x = rot.y = rot.z = 0.0;
    scale.x = scale.y = scale.z = 1.0;
    pos.x = 0.0;
    pos.y = 0.0;
    pos.z = -4.0;
}

_quad::~_quad()
{
    delete myTex;
}

void _quad::drawQuad()
{
    glPushMatrix();
        glColor3f(0.0,0.5,1.0); // Set base color

        myTex->bindTexture();

        glTranslatef(pos.x, pos.y, pos.z); // Place the object
        glRotatef(rot.x, 1.0, 0.0, 0.0); // Rotation around x
        glRotatef(rot.y, 0.0, 1.0, 0.0); // Rotation around y
        glRotatef(rot.z, 0.0, 0.0, 1.0); // Rotation around z
        glScalef(scale.x, scale.y, scale.z); // Resize the object

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, vboTex);
        glTexCoordPointer(2, GL_FLOAT, 0, (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, vboPos);
        glVertexPointer(3, GL_FLOAT, 0, (void*)0);

        glDrawArrays(GL_QUADS, 0, 4);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();
}

void _quad::initQuad(char* filename)
{
    glGenBuffers(1,&vboPos);
    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_DYNAMIC_DRAW);

    glGenBuffers(1,&vboTex);
    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_DYNAMIC_DRAW);

    myTex->loadTexture(filename);
}

void _quad::updateQuad()
{
    float texCoord[8] = {xMax, yMin,
                         xMax, yMax,
                         xMin, yMax,
                         xMin, yMin};

    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(texCoord), texCoord);
}

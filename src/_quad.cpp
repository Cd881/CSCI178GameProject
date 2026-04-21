#include "_quad.h"

_quad::_quad()
{
    rot.x = rot.y = rot.z = 0.0f;
    scale.x = scale.y = scale.z = 1.0f;
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = -4.0f;

    myTex = new _textureLoader();
}

_quad::~_quad()
{
    delete myTex;
    myTex = nullptr;
}

void _quad::drawQuad()
{
    glPushMatrix();
        glColor3f(0.0f, 0.5f, 1.0f);

        if (myTex)
            myTex->bindTexture();

        glTranslatef(pos.x, pos.y, pos.z);
        glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
        glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
        glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
        glScalef(scale.x, scale.y, scale.z);

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
    glGenBuffers(1, &vboPos);
    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &vboTex);
    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_DYNAMIC_DRAW);

    if (filename && myTex)
        myTex->loadTexture(filename);
}

void _quad::updateQuad()
{
    float texCoord[8] = {
        xMax, yMin,
        xMax, yMax,
        xMin, yMax,
        xMin, yMin
    };

    glBindBuffer(GL_ARRAY_BUFFER, vboTex);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(texCoord), texCoord);
}

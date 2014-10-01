#include <GL/glu.h>
#include <GL/glut.h>

#include "cube.h"
#include "mainwindow.h"

// cube ///////////////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

// vertex attributes for glDrawElements() and glDrawRangeElement() ============
// vertex array
GLfloat vertices[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
                       1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
                       1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
                      -1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
                      -1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
                       1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

// normal array
GLfloat normals[]  = { 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
                       1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
                       0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
                      -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
                       0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
                       0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)

// index array of vertex array for glDrawElements() & glDrawRangeElement()
GLubyte indices[]  = { 0, 1, 2,   2, 3, 0,      // front
                       4, 5, 6,   6, 7, 4,      // right
                       8, 9,10,  10,11, 8,      // top
                      12,13,14,  14,15,12,      // left
                      16,17,18,  18,19,16,      // bottom
                      20,21,22,  22,23,20 };    // back

// color array
GLfloat colors_01[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
                        1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

                        1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
                        0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

                        1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
                        0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

                        1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
                        0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

                        0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
                        1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

                        0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
                        0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4

// color array
GLfloat colors_02[] = { 1, 1, 1,   1, 1, 1,   1, 1, 1,      // v0-v1-v2 (front)
                        0, 0, 0,   0, 0, 0,   0, 0, 0,      // v2-v3-v0

                        0, 0, 0,   0, 0, 0,   0, 0, 0,      // v0-v3-v4 (right)
                        1, 1, 1,   1, 1, 1,   1, 1, 1,      // v4-v5-v0

                        1, 1, 1,   1, 1, 1,   1, 1, 1,      // v0-v5-v6 (top)
                        0, 0, 0,   0, 0, 0,   0, 0, 0,      // v6-v1-v0

                        0, 0, 0,   0, 0, 0,   0, 0, 0,      // v1-v6-v7 (left)
                        1, 1, 1,   1, 1, 1,   1, 1, 1,      // v7-v2-v1

                        1, 1, 1,   1, 1, 1,   1, 1, 1,      // v7-v4-v3 (bottom)
                        0, 0, 0,   0, 0, 0,   0, 0, 0,      // v3-v2-v7

                        1, 1, 1,   1, 1, 1,   1, 1, 1,      // v4-v7-v6 (back)
                        0, 0, 0,   0, 0, 0,   0, 0, 0 };    // v6-v5-v4


Cube::Cube()
{
    cubeHited = false;
    x = 0;
    y = 0;
    z = 0;
}

void Cube::drawCube()
{
    if (isRunning)
        return;

    // enable and specify pointers to vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glNormalPointer(GL_FLOAT, 0, normals);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    if (cubeHited)
        glColorPointer(3, GL_FLOAT, 0, colors_01);
    else
        glColorPointer(3, GL_FLOAT, 0, colors_02);

    glPushMatrix();
    glPushName(cubeId);

    glTranslatef(x, y, z);

    /**
    if (cubeHited)
        glColor3f(0.2f, 0.2f, 0.8f);
    else
        glColor3f(0.7f, 0.7f, 0.7f);
    */


    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

    glPopName();
    glPopMatrix();

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Cube::setXYZ(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Cube::setX(float x)
{
    this->x = x;
}

float Cube::getX()
{
    return x;
}

void Cube::setY(float y)
{
    this->y = y;
}

float Cube::getY()
{
    return y;
}

void Cube::setZ(float z)
{
    this->z = z;
}

float Cube::getZ()
{
    return z;
}

void Cube::setCubeId(int id)
{
    cubeId = id;
}

int Cube::getCubeId()
{
    return cubeId;
}

void Cube::setCubeAsHited(bool hit)
{
    if (hit)
        cubeHited = true;
    else
        cubeHited = false;
}

bool Cube::isHited()
{
    return cubeHited;
}


#ifndef CUBE_H
#define CUBE_H

#include <QGLFunctions>

class Cube
{
public:
    Cube();
    void drawCube();

    void setXYZ(float x, float y, float z);

    void setX(float x);
    float getX();
    void setY(float y);
    float getY();
    void setZ(float z);
    float getZ();

    void setCubeId(int id);
    int getCubeId();

    void setCubeAsHited(bool hit);
    bool isHited();

private:
    bool cubeHited;
    int cubeId;

    float x;
    float y;
    float z;
};

#endif // CUBE_H

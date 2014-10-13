#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "cube.h"

#include <QGLWidget>
#include <QGLFunctions>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QList>

class GLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0, int rows = 1, int cols = 1, int slices = 1);
    ~GLWidget();

    QSize sizeHint() const;
    void setCubeList(QList<Cube> cubo);
    QList<Cube> getCubeList();

    int getCubeRows();
    int getCubeCols();
    int getCubeSlices();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void clearCubesHited();
    void displayCubesNotHiteds(bool value);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent* event);
    QSize minimumSizeHint() const;

    void initLights();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void drawCubes();
    int selectCube(int mouseX, int mouseY);
    int processHits(int hitCount, GLuint* buffer);
    void initCubePositions();

    bool displayOnlyCubesHiteds;
    int cameraDistance;
    int xRot;
    int yRot;
    int zRot;

    int hitId;

    int cubeRows;
    int cubeCols;
    int cubeSlices;

    QPoint lastPos;
    QPoint lastMousePressPos;
    QList<Cube> cubeList;
};

#endif // GLWIDGET_H

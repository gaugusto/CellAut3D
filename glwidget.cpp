#include "glwidget.h"

#include <QDebug>
#include <GL/glut.h>
#include <GL/glu.h>

#define FOV_Y 30.0

GLWidget::GLWidget(QWidget *parent, int rows, int cols, int slices) :
    QGLWidget(parent)
{
    drawOnlyCubesHiteds = false;
    cameraDistance = 60.0f;
    xRot = 0;
    yRot = 0;
    zRot = 0;

    cubeRows = rows;
    cubeCols = cols;
    cubeSlices = slices;

    hitId = -1;
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::setCubeList(QList<Cube> cubo)
{
    cubeList = cubo;
}

QList<Cube> GLWidget::getCubeList()
{
    return cubeList;
}

int GLWidget::getCubeRows()
{
    return cubeRows;
}

int GLWidget::getCubeCols()
{
    return cubeCols;
}

int GLWidget::getCubeSlices()
{
    return cubeSlices;
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}

void GLWidget::clearCubesHited()
{
    for (int i = 0; i < cubeList.size(); ++i)
        cubeList[i].setCubeAsHited(false);
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    lastMousePressPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (lastMousePressPos != event->pos())
        return;

    if (event->button() == Qt::LeftButton)
    {
        hitId = selectCube(event->x(), event->y());
        if (hitId < 0)
            return;

        if(!cubeList[hitId].isHited())
            cubeList[hitId].setCubeAsHited(true);
        else
            cubeList[hitId].setCubeAsHited(false);

        updateGL();
    }

    //qDebug() << cubeHitList->size();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton)
    {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_V)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        updateGL();
    }
    else if (event->key() == Qt::Key_D)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        updateGL();
    }
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    cameraDistance -= (event->angleDelta().y()/4) * 0.2f;

    updateGL();
}

void GLWidget::initLights()
{
    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {0.2f, 0.2f, 0.2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {0.7f, 0.7f, 0.7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
}

void GLWidget::initializeGL()
{
    glShadeModel(GL_FLAT);                    // GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable/disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClearStencil(0);
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);

    initLights();
    initCubePositions();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -cameraDistance);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);

    drawCubes();
}

void GLWidget::resizeGL(int width, int height)
{
    // Square
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    // set perspective viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1, -1,1, 1.0,10000.0);
    //gluPerspective(FOV_Y,  (float)width / height, 1.0f, 10000.0f);
}

void GLWidget::drawCubes()
{
    for (int i = 0; i < cubeList.size(); ++i)
    {
        cubeList[i].setCubeId(i);

        if (drawOnlyCubesHiteds)
        {
            if (cubeList[i].isHited())
                cubeList[i].drawCube();
        }
        else
            cubeList[i].drawCube();
    }
}

int GLWidget::selectCube(int mouseX, int mouseY)
{
    const int BUFFER_SIZE = 512;
    GLuint selectionBuffer[BUFFER_SIZE];
    memset(selectionBuffer, 0, sizeof(int) * BUFFER_SIZE);
    GLint viewport[4];
    glGetIntegerv (GL_VIEWPORT, viewport);

    // tell OpenGL to use selection buffer
    glSelectBuffer(BUFFER_SIZE, selectionBuffer);

    // enter selection mode
    glRenderMode(GL_SELECT);

    // init name stack
    glInitNames();

    // Pick Matrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(mouseX, viewport[3] - mouseY, 2, 2, viewport);
    //gluPerspective(FOV_Y,  (float)viewport[2] / viewport[3], 0.1f, 1000.0f);
    glFrustum(-1,1, -1,1, 1.0,10000.0);

    // view transform
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glShadeModel(GL_FLAT);

    // draw cubes
    drawCubes();

    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    //glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();
    //glFlush();

    // leave selection mode
    int hitCount = glRenderMode(GL_RENDER);

    // process hits
    if(hitCount > 0)
        return processHits(hitCount, selectionBuffer);
    else
        return -1; // not hit
}

int GLWidget::processHits(int hitCount, GLuint* buffer)
{
    if(hitCount <= 0 || !buffer)
        return -1;

    GLuint nameCount, minZ, maxZ;
    GLuint hitZ = 0xffffffff;   // init with biggest value

    int hitId = 0;
    for(int i = 0; i < hitCount; ++i)
    {
        nameCount = *buffer++;
        minZ = *buffer++;
        maxZ = *buffer++;

        if(minZ < hitZ)
        {
            hitZ = minZ;
            hitId = (int)*buffer;
        }

        // consume other entries in the buffer
        for(int j = 0; j < (int)nameCount; ++j, ++buffer)
            ;//qDebug() << "Name: " << *buffer << endl;
    }

    return hitId;
}

void GLWidget::initCubePositions()
{
    // init cube positions
    const float STEP  = 4.0f;
    float startX = -STEP * (cubeCols - 1) / 2.0f;
    float startY = STEP * (cubeRows - 1) / 2.0f;
    float startZ = STEP * (cubeSlices- 1) / 2.0f;

    for(int k = 0; k < cubeSlices; ++k)        // z-direction
        for(int j = 0; j < cubeRows; ++j)      // y-direction
            for(int i = 0; i < cubeCols; ++i)  // x-direction
            {
                Cube cubo;
                cubo.setXYZ(startX + (i*STEP), startY - (j*STEP), startZ - (k*STEP));
                cubeList.append(cubo);
            }
}

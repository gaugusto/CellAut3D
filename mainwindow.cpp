#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "jogodavida.h"
#include "flocosneve.h"
#include "testneighbors.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    glwidget = createGLWidget(ui->spinBoxRows->value(),
                              ui->spinBoxCols->value(),
                              ui->spinBoxSlices->value());

    tr_implemented = jogo_da_vida;
    iterationCounter = 0;
    isRunning = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,
            SLOT(iterarButtonClicked()));

    connect(ui->cbOnlyCubesHited, SIGNAL(clicked(bool)),
            glwidget, SLOT(displayCubesNotHiteds(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iterarButtonClicked()
{
    if (tr_implemented == jogo_da_vida)
    {
        JogoDaVida *jv = new JogoDaVida(this,
                                        glwidget->getCubeRows(),
                                        glwidget->getCubeCols(),
                                        glwidget->getCubeSlices());

        connect(jv, SIGNAL(iterated()), this,
                SLOT(gridIterated()));

        jv->setCubeList(glwidget->getCubeList());
        jv->processRules();
        glwidget->setCubeList(jv->getCubeList());
    }

    if (tr_implemented == flocos_de_neve)
    {
        FlocosNeve *fn = new FlocosNeve(this,
                            glwidget->getCubeRows(),
                            glwidget->getCubeCols(),
                            glwidget->getCubeSlices());

        connect(fn, SIGNAL(iterated()), this,
                SLOT(gridIterated()));

        fn->setCubeList(glwidget->getCubeList());
        fn->processRules();
        glwidget->setCubeList(fn->getCubeList());
    }

    if (tr_implemented == testar_vizinhos)
    {
        TestNeighbors *tn = new TestNeighbors(this,
                                              glwidget->getCubeRows(),
                                              glwidget->getCubeCols(),
                                              glwidget->getCubeSlices());
        connect(tn, SIGNAL(iterated()), this,
                SLOT(gridIterated()));

        tn->setCubeList(glwidget->getCubeList());
        tn->processRules();
        glwidget->setCubeList(tn->getCubeList());
    }

    glwidget->updateGL();
}

void MainWindow::zerarButtonClicked()
{
    glwidget->clearCubesHited();
    ui->lblIteration->setText(tr("Iteração: %0").
                              arg(iterationCounter = 0));

    timer->stop();
    ui->btnPlay->setText("&Play ->");
}

void MainWindow::playButtonClicked()
{
    if (!isRunning)
        startRunning();
    else
        stopRunning();
}

void MainWindow::spinRowsChanged(int value)
{
    stopRunning();

    delete glwidget;
    glwidget = createGLWidget(value,
                              ui->spinBoxCols->value(),
                              ui->spinBoxSlices->value());
}

void MainWindow::spinColsChanged(int value)
{
    stopRunning();

    delete glwidget;
    glwidget = createGLWidget(ui->spinBoxRows->value(),
                              value,
                              ui->spinBoxSlices->value());
}

void MainWindow::spinSlicesChanged(int value)
{
    stopRunning();

    delete glwidget;
    glwidget = createGLWidget(ui->spinBoxRows->value(),
                              ui->spinBoxCols->value(),
                              value);
}

void MainWindow::chooseRTChanged(int index)
{
    switch(index)
    {
    case 0:
        tr_implemented = jogo_da_vida;
        break;
    case 1:
        tr_implemented = flocos_de_neve;
        break;
    case 2:
        tr_implemented = testar_vizinhos;
        break;
    default:
        tr_implemented = jogo_da_vida;
    }
}

void MainWindow::gridIterated()
{
    ui->lblIteration->setText(tr("Iteração: %0").
                              arg(++iterationCounter));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F11)
    {
        if (!isFullScreen())
            showFullScreen();
        else if (isFullScreen())
            showNormal();
    }
}

GLWidget *MainWindow::createGLWidget(int rows, int cols, int slices)
{
    GLWidget *glwidget = new GLWidget(ui->centralWidget, rows, cols, slices);
    glwidget->setObjectName(QStringLiteral("glwidget"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(glwidget->sizePolicy().hasHeightForWidth());
    glwidget->setSizePolicy(sizePolicy);

    ui->horizontalLayout_5->addWidget(glwidget);

    return glwidget;
}

void MainWindow::startRunning()
{
    if (isRunning)
        return;

    timer->start(500);
    ui->btnPlay->setText("&Parar!");

    isRunning = !isRunning;
}

void MainWindow::stopRunning()
{
    if (!isRunning)
        return;

    timer->stop();
    ui->btnPlay->setText("&Play ->");

    isRunning = !isRunning;
}

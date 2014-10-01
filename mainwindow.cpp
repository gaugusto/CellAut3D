#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    glwidget = createGLWidget(ui->spinBoxRows->value(),
                              ui->spinBoxCols->value(),
                              ui->spinBoxSlices->value());

    iterationCounter = 0;
    isRunning = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,
            SLOT(iterarButtonClicked()));

    connect(ui->spinBoxRows, SIGNAL(valueChanged(int)),
            this, SLOT(spinRowsChanged(int)));
    connect(ui->spinBoxCols, SIGNAL(valueChanged(int)),
            this, SLOT(spinColsChanged(int)));
    connect(ui->spinBoxSlices, SIGNAL(valueChanged(int)),
            this, SLOT(spinSlicesChanged(int)));

    connect(ui->iterarButton, SIGNAL(clicked()),
            this, SLOT(iterarButtonClicked()));
    connect(ui->zerarButton, SIGNAL(clicked()),
            this, SLOT(zerarButtonClicked()));
    connect(ui->btnPlay, SIGNAL(clicked()),
            this, SLOT(playButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iterarButtonClicked()
{
    jv = new JogoDaVida(this,
                        glwidget->getCubeRows(),
                        glwidget->getCubeCols(),
                        glwidget->getCubeSlices());

    connect(jv, SIGNAL(iterated()), this,
            SLOT(jvIterated()));

    jv->setCubeList(glwidget->getCubeList());
    jv->processRules();
    glwidget->setCubeList(jv->getCubeList());
    glwidget->drawOnlyCubesHiteds = true;
    glwidget->updateGL();
}

void MainWindow::zerarButtonClicked()
{
    glwidget->drawOnlyCubesHiteds = false;
    glwidget->clearCubesHited();
    ui->lblIteration->setText(tr("Iteração: %0").
                              arg(iterationCounter = 0));

    timer->stop();
    ui->btnPlay->setText("&Play ->");
}

void MainWindow::playButtonClicked()
{
    if (!isRunning)
    {
        timer->start(500);
        ui->btnPlay->setText("&Parar!");
    }
    else
    {
        timer->stop();
        ui->btnPlay->setText("&Play ->");
    }

    isRunning = !isRunning;
}

void MainWindow::spinRowsChanged(int value)
{
    delete glwidget;
    glwidget = createGLWidget(value,
                              ui->spinBoxCols->value(),
                              ui->spinBoxSlices->value());
}

void MainWindow::spinColsChanged(int value)
{
    delete glwidget;
    glwidget = createGLWidget(ui->spinBoxRows->value(),
                              value,
                              ui->spinBoxSlices->value());
}

void MainWindow::spinSlicesChanged(int value)
{
    delete glwidget;
    glwidget = createGLWidget(ui->spinBoxRows->value(),
                              ui->spinBoxCols->value(),
                              value);
}

void MainWindow::jvIterated()
{
    ui->lblIteration->setText(tr("Iteração: %0").
                              arg(++iterationCounter));
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


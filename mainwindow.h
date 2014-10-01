#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "glwidget.h"
#include "jogodavida.h"

namespace Ui {
class MainWindow;
}

extern bool isRunning;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void iterarButtonClicked();
    void zerarButtonClicked();
    void playButtonClicked();

    void spinRowsChanged(int value);
    void spinColsChanged(int value);
    void spinSlicesChanged(int value);

    void jvIterated();

private:
    GLWidget *createGLWidget(int rows, int cols, int slices);
    Ui::MainWindow *ui;
    GLWidget *glwidget;
    JogoDaVida *jv;
    QTimer *timer;
    unsigned int iterationCounter;
};

#endif // MAINWINDOW_H

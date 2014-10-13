#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "glwidget.h"

enum TR {jogo_da_vida, flocos_de_neve, testar_vizinhos};

namespace Ui {
class MainWindow;
}

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

    void cbOnlyCubesHitedChanged(bool value);

    void chooseRTChanged(int index);

    void gridIterated();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    GLWidget *createGLWidget(int rows, int cols, int slices);
    void startRunning();
    void stopRunning();
    Ui::MainWindow *ui;
    GLWidget *glwidget;
    QTimer *timer;
    unsigned int iterationCounter;
    bool isRunning;
    bool onlyCubesHited;

    TR tr_implemented; // Regras de transição implementadas (enum)
};

#endif // MAINWINDOW_H

#ifndef JOGODAVIDA_H
#define JOGODAVIDA_H

#include <QObject>
#include <QList>
#include <QDebug>

#include "cube.h"

class JogoDaVida : public QObject
{
    Q_OBJECT
public:
    explicit JogoDaVida(QObject *parent = 0, int rows = 1, int cols = 1, int slices = 1);
    void setCubeList(QList<Cube> list);
    QList<Cube> getCubeList();
    void processRules();

public slots:
    void clearTableJV();

signals:
    void iterated();

private:
    void processNeighbors(int id);
    void sliceNeighbors(int id);
    void rowNeighbors(int id, bool slideCurrent);
    void tableJVtoCubeList();

    QList<Cube> cubeList;
    QList<bool> tableJV;

    int tableRows;
    int tableCols;
    int tableSlices;
    int sliceSize;
    int countNeighbors;
};

#endif // JOGODAVIDA_H

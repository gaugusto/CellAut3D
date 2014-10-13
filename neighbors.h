#ifndef NEIGHBORS_H
#define NEIGHBORS_H

#include <QObject>
#include <QDebug>

#include "cube.h"

class Neighbors : public QObject
{
    Q_OBJECT
public:
    explicit Neighbors(QObject *parent = 0, int rows = 1, int cols = 1, int slices = 1);

    void setCubeList(QList<Cube> list);
    QList<Cube> getCubeList();
    virtual void processRules();

protected:
    void tableToCubeList();
    void processNeighbors(int id);
    QList<Cube> cubeList;
    QList<Cube> neighborsList;
    int countNeighborsHiteds;
    QList<bool> table;

public slots:
    void cleartable();

signals:
    void iterated();

private:

    void sliceNeighbors(int id);
    void rowNeighbors(int id, bool slideCurrent);
    int tableRows;
    int tableCols;
    int tableSlices;
    int sliceSize;
    int tableSize;

};

#endif // NEIGHBORS_H

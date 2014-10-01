#ifndef TRANSITIONRULES_H
#define TRANSITIONRULES_H

#include <QObject>
#include "cube.h"

class TransitionRules : public QObject
{
    Q_OBJECT
public:
    explicit TransitionRules(QObject *parent = 0, int rows = 1, int cols = 1, int slices = 1);
    void setCubeList(QList<Cube> list);
    QList<Cube> getCubeList();
    virtual void processRules();

protected:
    void tableJVtoCubeList();
    void processNeighbors(int id);
    int countNeighbors;
    QList<Cube> cubeList;
    QList<bool> tableJV;

public slots:
    void clearTableJV();

signals:
    void iterated();

private:

    void sliceNeighbors(int id);
    void rowNeighbors(int id, bool slideCurrent);
    int tableRows;
    int tableCols;
    int tableSlices;
    int sliceSize;
};

#endif // TRANSITIONRULES_H

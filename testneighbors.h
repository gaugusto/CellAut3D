#ifndef TESTNEIGHBORS_H
#define TESTNEIGHBORS_H

#include "neighbors.h"

class TestNeighbors : public Neighbors
{
    Q_OBJECT
public:
    explicit TestNeighbors(QObject *parent = 0, int rows = 0, int cols = 0, int slices = 0);
    void processRules();

signals:

public slots:

};

#endif // TESTNEIGHBORS_H

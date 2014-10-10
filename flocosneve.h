#ifndef FLOCOSNEVE_H
#define FLOCOSNEVE_H

#include "neighbors.h"

class FlocosNeve : public Neighbors
{
    Q_OBJECT
public:
    explicit FlocosNeve(QObject *parent = 0, int rows = 0, int cols = 0, int slices = 0);
    void processRules();

signals:

public slots:

};

#endif // FLOCOSNEVE_H

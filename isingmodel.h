#ifndef ISINGMODEL_H
#define ISINGMODEL_H

#include "transitionrules.h"

class IsingModel : public TransitionRules
{
    Q_OBJECT
public:
    explicit IsingModel(QObject *parent = 0, int rows = 1, int cols = 1, int slices = 1);
    void processRules();

signals:

public slots:

};

#endif // ISINGMODEL_H

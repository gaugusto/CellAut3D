#ifndef JOGODAVIDA_H
#define JOGODAVIDA_H

#include "neighbors.h"

class JogoDaVida : public Neighbors
{
    Q_OBJECT
public:
    explicit JogoDaVida(QObject *parent = 0, int rows = 1, int cols = 1, int slices = 1);
    void processRules();

signals:

public slots:

};

#endif // JOGODAVIDA_H

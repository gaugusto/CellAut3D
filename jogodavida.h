#ifndef JOGODAVIDA_H
#define JOGODAVIDA_H

#include "transitionrules.h"

class JogoDaVida : public TransitionRules
{
    Q_OBJECT
public:
    explicit JogoDaVida(QObject *parent = 0, int rows = 1, int cols = 1, int slices = 1);
    void processRules();

signals:

public slots:

};

#endif // JOGODAVIDA_H

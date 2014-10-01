#include "isingmodel.h"

#include "transitionrules.h"

IsingModel::IsingModel(QObject *parent, int rows, int cols, int slices) :
    TransitionRules(parent, rows, cols, slices)
{
}

void IsingModel::processRules()
{

}

#include "flocosneve.h"
#include "neighbors.h"

FlocosNeve::FlocosNeve(QObject *parent, int rows, int cols, int slices) :
    Neighbors(parent, rows, cols, slices)
{
}

void FlocosNeve::processRules()
{
    cleartable();

    for (int i = 0; i < cubeList.size(); ++i)
    {
        // Identifica os vizinhos de determinada célula
        processNeighbors(i);

        if (!cubeList[i].isHited() && countNeighborsHiteds == 3)
            table[i] = true;
    }

    tableToCubeList();

    emit iterated();
}

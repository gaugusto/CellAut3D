#include "testneighbors.h"

#include <QDebug>

TestNeighbors::TestNeighbors(QObject *parent, int rows, int cols, int slices) :
    Neighbors(parent, rows, cols, slices)
{
}

void TestNeighbors::processRules()
{
    cleartable();

    for (int i = 0; i < cubeList.size(); ++i)
    {
        if (cubeList[i].isHited())
        {
            processNeighbors(i); // Identifica os vizinhos de determinada célula
            for (int j = 0; j < neighborsList.size(); ++j)
                table[neighborsList[j].getCubeId()] = true;
        }
    }

    tableToCubeList();

    emit iterated();
}

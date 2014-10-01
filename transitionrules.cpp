#include "transitionrules.h"

TransitionRules::TransitionRules(QObject *parent, int rows, int cols, int slices) :
    QObject(parent)
{
    tableRows = rows;
    tableCols = cols;
    tableSlices = slices;
    countNeighbors = 0;
    sliceSize = tableRows*tableCols;
}

void TransitionRules::setCubeList(QList<Cube> list)
{
    cubeList = list;
}

QList<Cube> TransitionRules::getCubeList()
{
    return cubeList;
}

void TransitionRules::processRules()
{
    return;
}

void TransitionRules::clearTableJV()
{
    for (int i = 0; i < cubeList.size(); ++i)
        tableJV.append(false);
}

void TransitionRules::processNeighbors(int id)
{
    countNeighbors = 0;

    sliceNeighbors(id);

    if (id + sliceSize < sliceSize * tableSlices) // slice ++ (back)
        sliceNeighbors(id + sliceSize);

    if (id - sliceSize > 0) // slice -- (front)
        sliceNeighbors(id - sliceSize);
}

void TransitionRules::sliceNeighbors(int id)
{
    rowNeighbors(id, true); // side

    if (id % sliceSize >= tableRows) // up - side
        rowNeighbors(id - tableRows, false);

    if (id % sliceSize < (sliceSize - tableRows)) // down - side
        rowNeighbors(id + tableRows, false);
}

void TransitionRules::rowNeighbors(int id, bool slideCurrent)
{
    if (!slideCurrent)
        if (cubeList[id].isHited())
            countNeighbors++;

    if (id % tableCols > 0 ) // Vizinho na esquerda
        if (cubeList[id-1].isHited())
            countNeighbors++;

    if ((id+1) % tableCols > 0) // Vizinho na direita
        if (cubeList[id+1].isHited())
            countNeighbors++;
}

void TransitionRules::tableJVtoCubeList()
{
    for (int i = 0; i < cubeList.size(); ++i)
        cubeList[i].setCubeAsHited(tableJV[i]);
}

#include "neighbors.h"

Neighbors::Neighbors(QObject *parent, int rows, int cols, int slices) :
    QObject(parent)
{
    tableRows = rows;
    tableCols = cols;
    tableSlices = slices;
    countNeighbors = 0;
    sliceSize = tableRows*tableCols;
}

void Neighbors::setCubeList(QList<Cube> list)
{
    cubeList = list;
}

QList<Cube> Neighbors::getCubeList()
{
    return cubeList;
}

void Neighbors::processRules()
{
    return;
}

void Neighbors::cleartable()
{
    for (int i = 0; i < cubeList.size(); ++i)
        table.append(false);
}

void Neighbors::processNeighbors(int id)
{
    countNeighbors = 0;

    sliceNeighbors(id); // Fatia Atual

    if (id + sliceSize < sliceSize * tableSlices) // Fatia de Trás
        sliceNeighbors(id + sliceSize);

    if (id - sliceSize > 0) // Fatia da Frente
        sliceNeighbors(id - sliceSize);
}

void Neighbors::sliceNeighbors(int id)
{
    rowNeighbors(id, true); // Lados - linha atual

    if (id % sliceSize >= tableRows) // Lados - linha acima
        rowNeighbors(id - tableRows, false);

    if (id % sliceSize < (sliceSize - tableRows)) // Lados - linha abaixo
        rowNeighbors(id + tableRows, false);
}

void Neighbors::rowNeighbors(int id, bool slideCurrent)
{
    if (!slideCurrent)
        if (cubeList[id].isHited())
            countNeighbors++; // Conto o vizinho do meio apenas se não estiver na fatia atual

    if (id % tableCols > 0 ) // Vizinho na esquerda
        if (cubeList[id-1].isHited())
            countNeighbors++;

    if ((id+1) % tableCols > 0) // Vizinho na direita
        if (cubeList[id+1].isHited())
            countNeighbors++;
}

void Neighbors::tabletoCubeList()
{
    for (int i = 0; i < cubeList.size(); ++i)
        cubeList[i].setCubeAsHited(table[i]);
}

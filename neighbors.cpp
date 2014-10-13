#include "neighbors.h"

Neighbors::Neighbors(QObject *parent, int rows, int cols, int slices) :
    QObject(parent)
{
    tableRows = rows;
    tableCols = cols;
    tableSlices = slices;
    sliceSize = tableRows*tableCols;
    tableSize = sliceSize*tableSlices;
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
    neighborsList.clear();
    countNeighborsHiteds = 0;
    sliceNeighbors(id); // Fatia Atual

    if (id + sliceSize < tableSize) // Fatia de Trás
        sliceNeighbors(id + sliceSize);
    else if (tableSlices > 1)
        sliceNeighbors((id + sliceSize) % sliceSize);

    if (id - sliceSize > 0) // Fatia da Frente
        sliceNeighbors(id - sliceSize);
    else if (tableSlices > 1)
        sliceNeighbors((id + (tableSize) - sliceSize) % (tableSize));
}

static int normalizeIndex(int index)
{
    if (index < 0)
        return index * -1;
    else
        return index;
}

void Neighbors::sliceNeighbors(int id)
{
    rowNeighbors(id, true); // linha atual

    if (id % sliceSize >= tableRows) // linha acima
        rowNeighbors(id - tableRows, false);
    else
        rowNeighbors(sliceSize - tableRows + id, false);

    if (id % sliceSize < (sliceSize - tableRows)) // linha abaixo
        rowNeighbors(id + tableRows, false);
    else
        rowNeighbors(normalizeIndex(sliceSize - tableRows - id), false);
}

void Neighbors::rowNeighbors(int id, bool slideCurrent)
{
    if (!slideCurrent)
        if (cubeList[id].isHited())
            countNeighborsHiteds++; // Adiciono o vizinho do meio apenas se não estiver na fatia atual

    neighborsList.append(cubeList[id]);

    if (id % tableCols > 0)
    {
        neighborsList.append(cubeList[id-1]);
        if (cubeList[id-1].isHited())
            countNeighborsHiteds++; //Adiciono o vizinho na esquerda
    }
    else
    {
        neighborsList.append(cubeList[id+tableCols-1]);
        if (cubeList[id+tableCols-1].isHited())
        countNeighborsHiteds++; // Adiciono o vizinho do outro lado
    }

    if ((id+1) % tableCols > 0)
    {
        neighborsList.append(cubeList[id+1]);
        if (cubeList[id+1].isHited())
            countNeighborsHiteds++; // Adiciono o vizinho na direita
    }
    else
    {
        neighborsList.append(cubeList[id-tableCols+1]);
        if (cubeList[id-tableCols+1].isHited())
            countNeighborsHiteds++; // Adiciono o vizinho do outro lado
    }
}

void Neighbors::tableToCubeList()
{
    for (int i = 0; i < cubeList.size(); ++i)
        cubeList[i].setCubeAsHited(table[i]);
}

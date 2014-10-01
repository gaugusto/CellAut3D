#include "jogodavida.h"

JogoDaVida::JogoDaVida(QObject *parent, int rows, int cols, int slices) :
    QObject(parent)
{
    tableRows = rows;
    tableCols = cols;
    tableSlices = slices;
    countNeighbors = 0;
    sliceSize = tableRows*tableCols;
}

void JogoDaVida::setCubeList(QList<Cube> list)
{
    cubeList = list;
}

QList<Cube> JogoDaVida::getCubeList()
{
    return cubeList;
}

void JogoDaVida::processRules()
{
    clearTableJV();
    countNeighbors = 0;

    for (int i = 0; i < cubeList.size(); ++i)
    {
        // Identifica os vizinhos de determinada célula
        processNeighbors(i);

        // Nascimento
        // Uma célula nascerá quando houver exatamente
        // três células vizinhas vivas.
        if (!cubeList[i].isHited())
            if (countNeighbors == 3)
                tableJV[i] = true;

        if (cubeList[i].isHited())
        {
            // Sobrevivência:
            // Se uma célula tiver de duas a três células
            // vizinhas vivas, então ela sobrevive.
            if (countNeighbors == 2 || countNeighbors == 3) // 7 ou 6
                tableJV[i] = true;

            // Morte:
            // Se existir uma ou nenhuma célula vizinha viva,
            // então ela morre por ter ficado sozinha.
            if (countNeighbors <= 1)
                tableJV[i] = false;

            // Morte:
            // Se uma célula tiver quatro ou mais células vizinhas
            // vivas, então ela morre devido à superpopulação.
            if (countNeighbors >= 4)
                tableJV[i] = false;
        }
    }

    tableJVtoCubeList();

    emit iterated();
}

void JogoDaVida::clearTableJV()
{
    for (int i = 0; i < cubeList.size(); ++i)
        tableJV.append(false);
}

void JogoDaVida::processNeighbors(int id)
{
    countNeighbors = 0;

    sliceNeighbors(id);

    if (id + sliceSize < sliceSize * tableSlices) // slice ++ (back)
        sliceNeighbors(id + sliceSize);

    if (id - sliceSize > 0) // slice -- (front)
        sliceNeighbors(id - sliceSize);
}

void JogoDaVida::sliceNeighbors(int id)
{
    rowNeighbors(id, true); // side

    if (id % sliceSize >= tableRows) // up - side
        rowNeighbors(id - tableRows, false);

    if (id % sliceSize < (sliceSize - tableRows)) // down - side
        rowNeighbors(id + tableRows, false);
}

void JogoDaVida::rowNeighbors(int id, bool slideCurrent)
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

void JogoDaVida::tableJVtoCubeList()
{
    for (int i = 0; i < cubeList.size(); ++i)
        cubeList[i].setCubeAsHited(tableJV[i]);
}

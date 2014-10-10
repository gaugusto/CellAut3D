#include "jogodavida.h"
#include "neighbors.h"

JogoDaVida::JogoDaVida(QObject *parent, int rows, int cols, int slices) :
    Neighbors(parent, rows, cols, slices)
{

}

void JogoDaVida::processRules()
{
    cleartable();
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
                table[i] = true;

        if (cubeList[i].isHited())
        {
            // Sobrevivência:
            // Se uma célula tiver de duas a três células
            // vizinhas vivas, então ela sobrevive.
            if (countNeighbors == 2 || countNeighbors == 3) // 7 ou 6
                table[i] = true;

            // Morte:
            // Se existir uma ou nenhuma célula vizinha viva,
            // então ela morre por ter ficado sozinha.
            if (countNeighbors <= 1)
                table[i] = false;

            // Morte:
            // Se uma célula tiver quatro ou mais células vizinhas
            // vivas, então ela morre devido à superpopulação.
            if (countNeighbors >= 4)
                table[i] = false;
        }
    }

    tabletoCubeList();

    emit iterated();
}

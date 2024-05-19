#include "Arvore.cpp"
#include "stdio.h"

namespace huffmann
{

    Tree::BinaryNoList calcularFrequencia(std::string palavra)
    {
        Tree::BinaryNoList auxList;
        Tree::BinaryNo NodeList[256];
        for (int i = 0; i < palavra.length(); i++)
        {
            NodeList[palavra[i]].info = palavra[i];
            NodeList[palavra[i]].key++;
        }
        for (int i = 0; i < 256; i++)
        {
            if (NodeList[i].key != 0)
            {
                Tree::Binary *aux = new Tree::Binary(NodeList[i]);
                auxList.insertInOrder(*aux);
            }
        }
        return auxList;
    }
}
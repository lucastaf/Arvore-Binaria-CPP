#include "Arvore.cpp"
#include "stdio.h"

namespace huffmann
{
    using namespace Tree;
    BinaryList calcularFrequencia(std::string palavra)
    {
        BinaryList auxList;
        BinaryNo NodeList[256];
        for (int i = 0; i < palavra.length(); i++)
        {
            NodeList[palavra[i]].info = palavra[i];
            NodeList[palavra[i]].key++;
        }
        for (int i = 0; i < 256; i++)
        {
            if (NodeList[i].key != 0)
            {
                Binary *aux = new Binary(NodeList[i]);
                auxList.insertInOrder(aux);
            }
        }
        return auxList;
    }

    Binary generateHuffmannTree(BinaryList lista)
    {
        while (lista.getLength() > 1)
        {
            Binary primeiroItem = lista.getItem(0);
            Binary segundoItem = lista.getItem(1);
            int soma = primeiroItem.getKey() + segundoItem.getKey();

            Binary *novaArvore = new Tree::Binary({soma, NULL});
            novaArvore->insertLeft(&primeiroItem);
            novaArvore->insertRight(&segundoItem);
            lista.deleteItemById(0);
            lista.deleteItemById(0);
            lista.insertInOrder(novaArvore);
        }
        return lista.getItem(0);
    }

}
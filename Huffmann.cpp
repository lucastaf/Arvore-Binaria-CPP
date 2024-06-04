#include "Arvore.cpp"
#include "stdio.h"

namespace huffmann
{
    using namespace Tree;
    BinaryList calcularFrequencia(std::string palavra)
    {
        BinaryList auxList;
        BinaryInfo<char> NodeList[256];
        for (int i = 0; i < palavra.length(); i++)
        {
            NodeList[palavra[i]].info = palavra[i];
            NodeList[palavra[i]].key++;
        }
        for (int i = 0; i < 256; i++)
        {
            if (NodeList[i].key != 0)
            {
                Binary<char> *aux = new Binary<char>(NodeList[i]);
                auxList.insertInOrder(aux);
            }
        }
        return auxList;
    }

    Binary<char> generateHuffmannTree(BinaryList lista)
    {
        while (lista.getLength() > 1)
        {
            Binary<char> *primeiroItem = lista.getItem(0);
            Binary<char> *segundoItem = lista.getItem(1);
            int soma = primeiroItem->getKey() + segundoItem->getKey();

            Binary<char> *novaArvore = new Tree::Binary<char>({soma, char(NULL)});
            novaArvore->insertLeft(primeiroItem);
            novaArvore->insertRight(segundoItem);
            lista.deleteItemById(0);
            lista.deleteItemById(0);
            lista.insertInOrder(novaArvore);
        }
        return *lista.getItem(0);
    }

}
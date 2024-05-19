#include <iostream>

namespace Tree
{
    struct BinaryNo
    {
        int key = 0;
        char info = ' ';

        void print()
        {
            std::cout << this->key << "->" << this->info << ", \n";
        }
    };
    class Binary
    {
        BinaryNo info;
        Binary *esq = NULL, *dir = NULL;

        Binary insertLeft(BinaryNo info)
        {
            Binary *aux = new Binary(info);
            this->esq = aux;
            return *aux;
        }
        Binary insertRight(BinaryNo info)
        {
            Binary *aux = new Binary(info);
            this->dir = aux;
            return *aux;
        }

    public:
        Binary(BinaryNo info)
        {
            this->info = info;
        }

        int countNodes()
        {
            if (this == nullptr)
            {
                return 0;
            }
            return 1 + this->esq->countNodes() + this->dir->countNodes();
        }

    public:
        void prefixado()
        {
            if (this == nullptr)
                return;
            this->info.print();
            this->esq->prefixado();
            this->dir->prefixado();
        }
        void infixado()
        {
            if (this == nullptr)
                return;
            this->esq->infixado();
            this->info.print();
            this->dir->infixado();
        }
        void posfixado()
        {
            if (this == nullptr)
                return;
            this->esq->posfixado();
            this->dir->posfixado();
            this->info.print();
        }

    public:
        void inserir(Binary *newNode)
        {
            if (this->info.key > newNode->info.key)
            {
                if (this->esq == nullptr)
                    this->esq = newNode;
                else
                    this->esq->inserir(newNode);
            }
            else
            {
                if (this->dir == nullptr)
                    this->dir = newNode;
                else
                    this->dir->inserir(newNode);
            }
        }

        void inserir(BinaryNo info)
        {
            Binary *aux = new Binary(info);
            this->inserir(aux);
            
        }
    };

}
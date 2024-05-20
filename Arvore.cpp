#include "lde.h"

namespace Tree
{
    struct BinaryNo
    {
        int key = 0;
        char info = char(0);

        void print()
        {
            std::cout << this->key << "->" << this->info << ", \n";
        }
    };
    class Binary
    {
        BinaryNo info;
        Binary *esq = NULL, *dir = NULL;

    public:
        void insertLeft(Binary *info)
        {
            this->esq = info;
        }
        void insertRight(Binary *info)
        {
            this->dir = info;
        }

        Binary() {}

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
        int getKey()
        {
            return this->info.key;
        }
        char getInfo()
        {
            return this->info.info;
        }
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

        void deleteTree()
        {
            if (this == nullptr)
                return;
            if (this->esq != nullptr)
            {
                this->esq->deleteTree();
                delete this->esq;
            }
            if (this->dir != nullptr)
            {
                this->dir->deleteTree();
                delete this->dir;
            }
        }
    };

    class BinaryList : public LDE<Binary>
    {

    public:
        void insertInOrder(Binary *node)
        {
            if (node->getInfo() == 0)
                return;

            No<Binary> *aux = this->getNo(0);
            if (aux == nullptr)
            {
                this->push(*node);
                return;
            }
            for (int i = 0; aux != nullptr; aux = aux->eloF, i++)
            {
                if (aux->info.getKey() > node->getKey())
                {
                    this->insert(i, *node);
                    return;
                }
            }
            this->push(*node);
        }

        void print()
        {

            for (No<Binary> *aux = this->getNo(0); aux != nullptr; aux = aux->eloF)
                std::cout << aux->info.getKey() << "->" << aux->info.getInfo() << ", ";
        }
    };
}
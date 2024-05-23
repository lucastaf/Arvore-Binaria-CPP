#include "lde.h"

namespace Tree
{
    struct BinaryInfo
    {
        int key = 0;
        char info = char(0);
        void print()
        {
            std::cout << this->key << "->" << this->info << ", ";
        }
    };

    class Binary
    {
        BinaryInfo info;
        Binary *esq = NULL, *dir = NULL;

        bool isLeaf()
        {
            return this->esq == NULL && this->dir == NULL ? true : false;
        }

        int childCount()
        {
            if (this->esq != NULL && this->dir != NULL)
            {
                return 2;
            }
            if (this->esq != NULL || this->dir != NULL)
            {
                return 1;
            }
            return 0;
        }

        Binary *buscarArvore(char valor)
        {
            if (this->info.info == valor)
                return this;
            if (valor < this->info.info)
                return this->esq->buscarArvore(valor);
            else
                return this->dir->buscarArvore(valor);
        }

        bool removeNode(Binary *&raiz, int valor)
        {
            if (raiz == NULL)
                return false;
            if (valor == raiz->info.key)
            {
                if (raiz->esq == NULL && raiz->dir == NULL)
                { // Caso 1
                    delete raiz;
                    raiz = NULL;
                    return true;
                }
                if (raiz->esq == NULL && raiz->dir != NULL)
                { // Caso 2
                    Binary *aux = raiz;
                    raiz = raiz->dir;
                    delete aux;
                    return true;
                }
                if (raiz->esq != NULL && raiz->dir == NULL)
                { // Caso 2
                    Binary *aux = raiz;
                    raiz = raiz->esq;
                    delete aux;
                    return true;
                }
                // Caso 3
                int aux = raiz->esq->getHighestKey();
                raiz->info.key = aux;
                return raiz->removeNode(raiz->esq, aux);
            }
            if (valor < raiz->info.key)
                return raiz->removeNode(raiz->esq, valor);
            else
                return raiz->removeNode(raiz->dir, valor);
        }

        BinaryInfo getHighestInfo()
        {

            if (this->dir == nullptr)
            {
                return this->info;
            }
            else
            {
                return this->info;
            }
        }

        int getHighestKey()
        {
            if (this->dir == nullptr)
            {
                return this->getKey();
            }
            else
            {
                return this->dir->getHighestKey();
            }
        }

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

        Binary(BinaryInfo info)
        {
            this->info = info;
        }

    public:
        // Misc
        void prefixado(bool leafOnly = false)
        {
            if (this == nullptr)
                return;
            if (!leafOnly || this->childCount() == 0)
                this->info.print();
            this->esq->prefixado(leafOnly);
            this->dir->prefixado(leafOnly);
        }
        void infixado(bool leafOnly = false)
        {
            if (this == nullptr)
                return;
            this->esq->infixado(leafOnly);
            if (!leafOnly || this->childCount() == 0)
                this->info.print();
            this->dir->infixado(leafOnly);
        }
        void posfixado(bool leafOnly = false)
        {
            if (this == nullptr)
                return;
            this->esq->posfixado(leafOnly);
            this->dir->posfixado(leafOnly);
            if (!leafOnly || this->childCount() == 0)
                this->info.print();
        }

        // Get
        int getKey()
        {
            return this->info.key;
        }
        char getInfo()
        {
            return this->info.info;
        }
        bool buscar(char valor)
        {
            if (this == nullptr)
                return false;
            if (this->info.info == valor)
                return true;
            if (valor < this->info.info)
                return this->esq->buscar(valor);
            else
                return this->dir->buscar(valor);
        }
        int countNodes()
        {
            if (this == nullptr)
            {
                return 0;
            }
            return 1 + this->esq->countNodes() + this->dir->countNodes();
        }
        int countLeaf()
        {
            if (this == nullptr)
            {
                return 0;
            }
            if (this->childCount() == 0)
            {
                return 1;
            }
            return this->esq->countLeaf() + this->dir->countLeaf();
        }
        // Insert
        void inserir(Binary *newNode)
        {
            if (this->getKey() == 0 && this->childCount() == 0)
            {
                this->info = newNode->info;
                this->esq = newNode->esq;
                this->dir = newNode->dir;
                delete newNode;
                return;
            }
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

        void inserir(BinaryInfo info)
        {
            Binary *aux = new Binary(info);
            this->inserir(aux);
        }

        // Delete
        void deleteTree()
        {
            if (this == nullptr)
                return;
            this->esq->deleteTree();
            this->dir->deleteTree();
            delete this;
        }

        bool deleteItem(int item)
        {
            Binary *thisNode = this;
            return this->removeNode(thisNode, item);
        }
    };

    class BinaryList : public LDE<Binary *>
    {

    public:
        void insertInOrder(Binary *node)
        {
            if (node->getKey() == 0)
                return;

            No<Binary *> *aux = this->getNo(0);
            if (aux == nullptr)
            {
                this->push(node);
                return;
            }
            for (int i = 0; aux != nullptr; aux = aux->eloF, i++)
            {
                if (aux->info->getKey() > node->getKey())
                {
                    this->insert(i, node);
                    return;
                }
            }
            this->push(node);
        }

        void print()
        {

            for (No<Binary *> *aux = this->getNo(0); aux != nullptr; aux = aux->eloF)
                std::cout << aux->info->getKey() << "->" << aux->info->getInfo() << ", ";
            std::cout << "\n";
        }
    };
}
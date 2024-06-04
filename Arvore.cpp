#include "lde.h"

namespace Tree
{
    template <class tipoNo>
    struct BinaryInfo
    {
        int key = 0;
        tipoNo info;

        void print()
        {
            std::cout << this->key << "->" << this->info << ", ";
        }
    };

    template <class tipoNo>
    class Binary
    {
        int height = 0;
        BinaryInfo<tipoNo> info;

    public:
        int getHeight()
        {
            return (this == nullptr) ? 0 : this->height;
        }

        Binary *esq = NULL, *dir = NULL;

    private:
        bool isLeaf()
        {
            return this->esq == NULL && this->dir == NULL ? true : false;
        }

        void setHeight()
        {
            if (this == nullptr)
                return;
            if (this->esq != nullptr)
            {
                this->height = this->esq->getHeight() + 1;
            }
            if (this->dir != nullptr)
            {
                if (this->getHeight() <= this->dir->getHeight())
                {
                    this->height = this->dir->getHeight() + 1;
                }
            }
        }

        int childCount()
        {
            if (this == nullptr)
                return 0;
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

        BinaryInfo<tipoNo> getHighestInfo()
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

        Binary *simpleRightRotation()
        {
            if (this == nullptr)
                return nullptr;
            Binary *x = this->esq;
            Binary *t2 = x->dir;
            x->dir = this;
            this->esq = t2;
            this->setHeight();
            x->setHeight();
            return x;
        }
        Binary *simpleLeftRotation()
        {
            if (this == nullptr)
                return nullptr;
            Binary *y = this->dir;
            Binary *t2 = y->esq;
            y->esq = this;
            this->dir = t2;
            this->setHeight();
            y->setHeight();
            return y;
        }
        Binary *doubleRightRotation()
        {
            Binary *x = this->esq;
            Binary *w = x->dir;
            Binary *t2 = w->esq;
            Binary *t3 = w->dir;
            x->dir = t2;
            this->esq = t3;
            w->esq = x;
            w->dir = this;
            return w;
        }
        Binary *doubleLeftRotation()
        {
            Binary *y = this->dir;
            Binary *z = y->esq;
            Binary *t2 = z->esq;
            Binary *t3 = z->dir;
            this->dir = t2;
            z->esq = this;
            z->dir = y;
            y->esq = t3;
            return z;
        }
        Binary *rotacaoAVL()
        {
            if (this->esq->getHeight() > this->dir->getHeight())
            {
                if (this->esq->esq->getHeight() >= this->esq->dir->getHeight())
                    return this->simpleRightRotation();
                else
                    return this->doubleRightRotation();
            }
            else
            {
                if (this->dir->dir->getHeight() >= this->dir->esq->getHeight())
                    return this->simpleLeftRotation();
                else
                    return this->doubleLeftRotation();
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

        Binary(BinaryInfo<tipoNo> info)
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
        void print(int tab = 3)
        {
            std::cout << "\n";
            for (int i = 0; i < tab; i++)
                std::cout << " ";
            if (this == NULL)
            {
                std::cout << "*";
                return;
            }
            this->info.print();
            this->esq->print(tab + 3);
            this->dir->print(tab + 3);
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
            int heightDiference = this->esq->getHeight() - this->dir->getHeight();
            if (heightDiference == 2 || heightDiference == 2)
            {
                this->rotacaoAVL();
            }
            this->setHeight();
        }

        void inserir(BinaryInfo<tipoNo> info)
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

        //--------------Atividade Dia 28/05---------------//
        Binary *procuraNoNaoRecursivo(int key)
        {
            Binary *aux = this;
            while (aux->info.key != key && aux != nullptr)
            {
                if (aux->info.key > key)
                {
                    aux = aux->esq;
                }
                else
                {
                    aux = aux->dir;
                }
            }
            return aux;
        }

        int contagemDeNosNaoFolha()
        {
            // Uma solução seria reaproveitar as função ja feitas, mas seria mais lento:
            // return this->countNodes() - this->countLeaf();
            if (this == nullptr || this->childCount() == 0)
            {
                return 0;
            }
            return 1 + this->esq->contagemDeNosNaoFolha() + this->dir->contagemDeNosNaoFolha();
        }

        int calcularArvoreDeOperacoes()
        {
            if (this->info.info == "+")
            {
                return this->esq->calcularArvoreDeOperacoes() + this->dir->calcularArvoreDeOperacoes();
            }
            else if (this->info.info == "-")
            {
                return this->esq->calcularArvoreDeOperacoes() - this->dir->calcularArvoreDeOperacoes();
            }
            else if (this->info.info == "*")
            {
                return this->esq->calcularArvoreDeOperacoes() * this->dir->calcularArvoreDeOperacoes();
            }
            else if (this->info.info == "/")
            {
                return this->esq->calcularArvoreDeOperacoes() / this->dir->calcularArvoreDeOperacoes();
            }
            return std::stoi(this->info.info);
        }

        bool testaBalanceado(int &maiorNivel, int currentNivel = 0)
        {
            int childCount = this->childCount();
            if (childCount == 1)
                return false;
            if (childCount == 0)
            {
                if (maiorNivel == 0)
                {
                    maiorNivel = currentNivel;
                }
                else if (maiorNivel != currentNivel)
                {
                    return false;
                }
                return true;
            }
            return this->esq->testaBalanceado(maiorNivel, currentNivel + 1) && this->dir->testaBalanceado(maiorNivel, currentNivel + 1);
        };
        void calcularMaiorSemOrdenacao(int &maiorValor)
        {
            if (this == nullptr)
                return;
            if (this->info.key > maiorValor)
            {
                maiorValor = this->info.key;
            }
            this->esq->calcularMaiorSemOrdenacao(maiorValor);
            this->dir->calcularMaiorSemOrdenacao(maiorValor);
        }
        void calcularMenorSemOrdencao(int &menorValor)
        {
            if (this == nullptr)
                return;
            if (this->info.key < menorValor)
            {
                menorValor = this->info.key;
            }
            this->esq->calcularMenorSemOrdencao(menorValor);
            this->dir->calcularMenorSemOrdencao(menorValor);
        }

        //-----------------------------------------------//
    };

    class BinaryList : public LDE<Binary<char> *>
    {

    public:
        void insertInOrder(Binary<char> *node)
        {
            if (node->getKey() == 0)
                return;

            No<Binary<char> *> *aux = this->getNo(0);
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

            for (No<Binary<char> *> *aux = this->getNo(0); aux != nullptr; aux = aux->eloF)
                std::cout << aux->info->getKey() << "->" << aux->info->getInfo() << ", ";
            std::cout << "\n";
        }
    };
}
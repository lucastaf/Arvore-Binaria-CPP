#include <iostream>

namespace Tree
{
    struct BinaryNo
    {
        int key = 0;
        char info = ' ';
    };
    class Binary
    {
        BinaryNo *info = new BinaryNo();
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
            this->info = &info;
        }
        Binary(){}
    private:
        int countNodes(Binary *raiz)
        {
            if (raiz == NULL)
                return 0;
            return 1 + this->countNodes(raiz->esq) + this->countNodes(raiz->dir);
        }

    public:
        int countNodes()
        {
            return 1 + this->countNodes(this->esq) + this->countNodes(this->dir);
        }

    private:
        void prefixado(Binary *raiz)
        {
            if (raiz == NULL)
                return;
            std::cout << raiz->info->key << " -> " << raiz->info->key << ", ";
            prefixado(raiz->esq);
            prefixado(raiz->dir);
        }
        void infixado(Binary *raiz)
        {
            if (raiz == NULL)
                return;
            prefixado(raiz->esq);
            std::cout << raiz->info->key << " -> " << raiz->info->key << ", ";
            prefixado(raiz->dir);
        }
        void posfixado(Binary *raiz)
        {
            if (raiz == NULL)
                return;
            prefixado(raiz->esq);
            std::cout << raiz->info->key << " -> " << raiz->info->key << ", ";
            prefixado(raiz->dir);
        }

    public:
        void prefixado()
        {
            this->prefixado(this);
        }
        void infixado()
        {
            this->infixado(this);
        }
        void posfixado()
        {
            this->posfixado(this);
        }
        
    private:
        void inserir(Binary *raiz, BinaryNo info){
            if(raiz == NULL){
                raiz = new Binary();
            }
            if(raiz->info == NULL){
                raiz->info = &info;
                return;
            }
            if(raiz->info->key > info.key){
                this->inserir(raiz->esq, info);
            } else{
                this->inserir(raiz->dir, info);
            }
        }
    public:
        void inserir(BinaryNo info){
            this->inserir(this, info);
        }

    
    };

}
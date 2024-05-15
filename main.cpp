#include "Arvore.cpp"
using namespace Tree;
int main()
{
    Binary *raiz = new Binary();

    raiz->inserir({0,'c'});


    raiz->prefixado();
    std::cout << "\n";
    raiz->infixado();
    std::cout << "\n";
    raiz->posfixado();
    std::cout << "\n";
    std::cout << raiz->countNodes();
}
#include "Arvore.cpp"
using namespace Tree;
using namespace std;
int main()
{
    //BinaryNo noRaiz = {0,'C'};
    Binary *raiz = new Binary({7, 'C'});

    raiz->inserir({2,'A'});
    raiz->inserir({3,'B'});
    raiz->inserir({1,'C'});
    raiz->inserir({5,'D'});

    raiz->prefixado();
    cout << "\n";
    raiz->infixado();
}
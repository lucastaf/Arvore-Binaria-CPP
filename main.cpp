#include "Huffmann.cpp"
using namespace std;
using namespace Tree;

int main()
{
    Binary<int> intABB;
    intABB.inserir({2, 3});
    intABB.inserir({4, 8});
    intABB.inserir({9, 5});
    intABB.inserir({1, 5});
    intABB.inserir({3, 7});

    intABB.print();


}
#include "Huffmann.cpp"
using namespace std;
using namespace Tree;

int main()
{
    BinaryList frequencyList = huffmann::calcularFrequencia("AAAAAAAAAAKOASDHNJIA");
    frequencyList.print();
    Binary finalTree = huffmann::generateHuffmannTree(frequencyList);

    finalTree.prefixado();
    cout << endl << finalTree.countLeaf() << endl;
    finalTree.prefixado(true);
}
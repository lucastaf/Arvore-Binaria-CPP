#include "Huffmann.cpp"
using namespace std;
using namespace Tree;

int main()
{
    BinaryList frequencyList = huffmann::calcularFrequencia("BOBOBO ME DA O CU");
    //frequencyList.print();
    Binary finalTree = huffmann::generateHuffmannTree(frequencyList);
    finalTree.prefixado();
    finalTree.infixado();
}
#include <iostream>
#include <string>
#include <binarysearchtree.h>

using namespace std;

int main()
{
    BinarySearchTree bintree(10);
    string temp1;
    string temp2;
    for(int i=0;i<8;i++){
        cin>>temp1;
        cin>>temp2;
        bintree.InsertBinarySearchTree(temp1,temp2);
    }

    bintree.FindCustomerIterative("Kresta");
    bintree.FindCustomerRecursive("Kresta");
    bintree.FindCustomerIterative("Acevedo");
    bintree.FindCustomerRecursive("Acevedo");

    cout<<"\n";
    bintree.InOrder(bintree.FindCustomerIterative("Parker"));

    bintree.InsertBinarySearchTree("Devin","294-1568");
    bintree.InsertBinarySearchTree("Morah","294-1882");
    bintree.InsertBinarySearchTree("Zembo","295-6622");

    cout<<"\n";
    bintree.InOrder();

    cout<<"\n";
    bintree.DeleteRandomNode(bintree.FindCustomerIterative("Kresta"));
    bintree.DeleteRandomNode(bintree.FindCustomerIterative("Najar"));
    bintree.DeleteRandomNode(bintree.FindCustomerIterative("Glosson"));

    bintree.InsertBinarySearchTree("Novak","294-1666");
    bintree.InsertBinarySearchTree("Gonzales","295-1882");

    cout<<"\n";
    bintree.InOrder();
    cout<<"\n";
    bintree.ReverseInOrder();
    cout<<"\n";
    bintree.PreOrder(bintree.tree[0]);
    cout<<"\n";
    bintree.PostOrderIterative(bintree.tree[0]);
    cout<<"\n";
    bintree.PostOrderRecursive(bintree.tree[0]);

    return 0;
}

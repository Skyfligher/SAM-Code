#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <string>
#include <iostream>
#include <node.h>
#include <stack>

using namespace std;

class BinarySearchTree
{
private:
    stack <node> stack;
    int count;



public:
    node * tree;
    BinarySearchTree(int temp);
    node* firstNode();
    void InsertBinarySearchTree(string temp1, string temp2);
    node* FindCustomerIterative(node* root, string temp);
    node* FindCustomerIterative(string temp);
    node* FindCustomerRecursive(node* root, string temp);
    node* FindCustomerRecursive(string temp);
    void DeleteRandomNode(node* toDelete);
    node* InOrderSuccessor(node* temp);
    string CustomerName(node* temp);
    string CustomerPhone(node* temp);
    void InOrder(node* temp);
    void InOrder();
    void ReverseInOrder(node* temp);
    void ReverseInOrder();
    void PreOrder(node* temp);
    void PostOrderIterative(node* temp);
    void PostOrderRecursive(node* temp);

};

#endif // BINARYSEARCHTREE_H

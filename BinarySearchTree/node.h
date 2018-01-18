#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>

using namespace std;
class node
{
public:
    node();
    node(string temp1, string temp2);
    bool operator ==(node temp);
    bool operator <(node temp);
    bool operator >(node temp);
    void operator =(node temp);

    node * lthread;
    node * rthread;
    node * lvalue;
    node * rvalue;
    string name;
    string number;
};

#endif // NODE_H

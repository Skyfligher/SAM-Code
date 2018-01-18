#ifndef STACK_H
#define STACK_H

#include <math.h>
#include <string>
#include <reallocate.h>
#include <iostream>

using namespace std;

class stack
{
public:
    stack();
    stack(int tsize, int tm, int tn, int tl0);
    void push(int sn, string temp);
    string pop(int sn);
    int k;
    int size;
    int m;
    int n;
    int l0;
    string *mem;
    int *top;
    int *base;
};
#endif // STACK_H

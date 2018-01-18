#include "stack.h"
#include <reallocate.h>
#include <iostream>

stack::stack()
{

}

stack::stack(int tsize, int tm, int tn, int tl0){

    size = tsize;
    m = tm;
    n = tn;
    l0 = tl0;

    mem = new string[size];
    top = new int[n];
    base = new int[n];

    for(int i = 0;i<n;i++){
        top[i]= floor((i-1)/(m * n))+l0;
        base[i] = top[i];
    }
}
////////////////////////////////////////push
void stack::push(int sn, string temp){
    k=sn;
    k=k-1; //matching k to arrays starting at 0
    top[k] = top[k]+1;
    if(top[k] > base[k+1]){
    cout<<"overflow "<<mem[base[k]]<<","<<mem[top[k]-1]<<",";
    reallocate<stack> re = new reallocate(this);
    cout<<mem[base[k]]<<","<<mem[top[k]]<<"/n";
    cout<<"Pushed "<<temp<<" to stack "<<sn<<"/n";

    }
    else{
        top[k] = temp;
        cout<<"Pushed "<<temp<<" to stack "<<sn<<"/n";
    }

}
////////////////////////////////////////pop(delete)
string stack::pop(int sn){
    if(top[sn] == base[sn]){
        return "undfl";
    }
    else{
        return mem[top[sn]];
        top[sn] = top[sn]-1;
        cout<<"Poped "<< mem[top[sn]]<<" from stack "<<sn<<"/n";
    }
}

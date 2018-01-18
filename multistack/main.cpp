#include <string>
#include <iostream>
#include <stack.h>

int size;
int start;
int stop;
int m;
int n;
int l0;


using namespace std;

int main()
{

    cout<<"Where does the array start?/n";
    cin>>start;

    cout<<"Where does the array end?/n";
    cin>>stop;

    cout<<"How much memory is used for the arrays?/n";
    cin>>m;

    cout<<"How many stacks will be used?/n";
    cin>>n;

    cout<<"Where should the stacks start?(L0)/n";
    cin>>l0;
    l0 = l0 - start;

    size = stop - start;
    stack main(size,m,n,l0);
    char function;
    int stacknum;
    string data;
    char cont = 'y';

    while(cont == 'y'){
        cin>>function;

        if(function == 'i'){
            cin>>stacknum;
            cin>>data;
            main.push(stacknum, data);
        }
        else{
            cin>>stacknum;
        }
        cin>>cont;
    }
    return 0;
}


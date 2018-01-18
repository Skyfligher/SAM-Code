#include <hashtable.h>
#include <iostream>

string temp;
hashTable table;

int main()
{

    for(int i = 0; i < 64; i++){
        cin>>temp;
        table.randadd(temp);
    }

    table.print();
    cout<<"\n\n";
    cout<<"First 30\n";
    for(int i = 0; i<30; i++){
        cin>>temp;
        table.randsearch(temp);
    }

    cout<<"\n\n";
    cout<<"Last 30\n";
    for(int i = 0; i<30; i++){
        cin>>temp;
        table.randsearch(temp);
    }

    return 0;
}

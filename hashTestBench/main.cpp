#include <hashtable.h>
#include <iostream>

string temp;
hashTable table;

int main()
{

    table.key = ("asdfasdf");
    table.hash();
    cout<<table.inithash;
   /*
    for(int i = 0; i < 116; i++){
        cin>>temp;
        table.linadd(temp);
    }

    table.print();
    cout<<"\n\n";
    cout<<"First 30\n";
    for(int i = 0; i<30; i++){
        cin>>temp;
        table.linsearch(temp);
    }

    cout<<"\n\n";
    cout<<"Last 30\n";
    for(int i = 0; i<30; i++){
        cin>>temp;
        table.linsearch(temp);
    }
*/
    return 0;
}

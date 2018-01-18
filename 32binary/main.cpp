#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string myfile;


int main()
{
    cout<<"text file name";
    ofstream file;
    file.open(myfile, ios::in | ios::binary);

}

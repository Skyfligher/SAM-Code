#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string myfile;
fstream file;
uint32_t num;



////////////////////////////////////////////////////Swapping Bytes
uint32_t swap(uint32_t source){
    uint32_t b0,b1,b2,b3;
    uint32_t swap;

    b0 = (source & 0x000000ff) << 24u;
    b1 = (source & 0x0000ff00) << 8u;
    b2 = (source & 0x00ff0000) >> 8u;
    b3 = (source & 0xff000000) >> 24u;

    swap = b0 | b1 | b2 | b3;
    return swap;

}


////////////////////////////////////////////////////Printing 32 bit Binary number
void printbine(uint32_t num){
    for(int i=31; i>=0; i--){
        cout<<((num>>i)& 1);
    }
}


////////////////////////////////////////////////////Printing 6 and 16 bit integers
void printint(uint32_t num){
    uint8_t b0,b1,b2;
    uint16_t bits;


    b0 = num & 0x000000FF;
    b1 = (num>>8) & 0x000000FF;
    bits = (b1<<8)|b0;

    b2 = (num>>16) & 0x0000003F;
    b2 = b2 & 0x3F;

    cout<<unsigned(b2);
    cout<<"\t";
    cout<<bits;

}

////////////////////////////////////////////////////Main Program
int main()
{
    cout<<"Give the binary files path.\n";
    cin>>myfile;
    file.open(myfile, ios::binary | ios::in);


    if(!file.is_open()){
    cout<<"File error.\n";
    return 0;
    }
    else{
      while(!file.eof()){
        file.read(reinterpret_cast<char*>(&num), sizeof(uint32_t));

        num = swap(num);
        printbine(num);
        cout<<"\t";
        printf("%08x",num);
        cout<<"\t";
        printint(num);
        cout<<"\n";

    }
}
    file.close();

}



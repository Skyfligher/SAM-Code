#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template<class T, int node>
class gclose
{
private:
    const static int nodes = node;

    T bmr[nodes][nodes];
    string bmrt[nodes][nodes];

    ifstream filein;

    string enums1[9] = {"Ada","Bob","Joe","Ken","Sam","Sue","Tim","Tom","Jim"};
    enum names {Ada,Bob,Joe,Ken,Sam,Sue,Tim,Tom,Jim};

    string enums2[7] = {"A","B","C","D","J","K","L"};
    enum alph {A,B,C,D,J,K,L};

public:
    void read(string filein);
    void warsh();
    void print(string fileout);
    int binor(T a, T b);

};


///////////////////////////////////////////////Reading txt file//////////////////////////////////////////////
template <class T, int node>
void gclose<T,node>::read(string filein){
    ifstream read(filein);
    string x;

    if(!read){
        cout<<"Unable to open the file "<<filein<<". Exiting program";
        exit(1);
    }

    for(int i=0; i<nodes; i++){
        for(int j=0; j<nodes; j++){
            read>>x;
            bmrt[i][j] = x;
        }
    }
    read.close();

    for(int i=0; i<nodes; i++){
        for(int j=0; j<nodes; j++){
            if(bmrt[i][j] == "1"){
                bmr[i][j] = 1;
            }
            else{
                bmr[i][j] = 0;
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////or overload/////////////////////////////////////////////////
template <class T, int node>
int gclose<T,node>::binor(T a,T b){
    if(a||b){
        return 1;
    }
    else{
        return 0;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////warshall's algorithm/////////////////////////////////////////////
template <class T, int node>
void gclose<T, node>::warsh(){

        for(int i=0;i<nodes;i++){
            for(int j=0;j<nodes;j++){
                if(bmr[j][i] == 1){
                    for(int k=0;k<nodes;k++){

                        bmr[j][k] = binor(bmr[j][k],bmr[i][k]);

                    }
                }
            }
        }
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////Print Function////////////////////////////////////////////////
template <class T, int node>
void gclose<T, node>::print(string fileout){
    ofstream out(fileout);

    out<<"\t";
    if(nodes == 9){
        for(int i=0; i<nodes; i++){
            out<<enums1[i]<<"\t";
        }
    }

    else{
        for(int i=0; i<nodes; i++){
            out<<enums1[i]<<"\t";
        }
    }
    out<<"\n";

    for(int i=0;i<nodes;i++){
        out<<enums2[i]<<"\t";
        for(int j=0; j<nodes; j++){
            out<<bmr[i][j]<<"\t";
        }
        out<<"\n";
    }
    out.close();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

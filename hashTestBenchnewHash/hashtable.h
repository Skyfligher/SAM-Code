#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class hashTable
{
public:
    hashTable();
    void linadd(string temp);
    void linsearch(string temp);
    void randadd(string temp);
    void randsearch(string temp);
    void hash();
    void print();

    string table[128][3];
    string key;
    int inithash;
    int probes;
    int hashes = 0;

};

#endif // HASHTABLE_H

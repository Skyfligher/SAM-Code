#ifndef VEHICLES_H
#define VEHICLES_H

#include <string>
using namespace std;


class car{
public:
    car();
    car(string temp, int drs);
    void print();
    string manuf;
    int doors;
};

class plane{

public:
    plane();
    plane(string temp, int drs, int eng);
    void print();
    string manuf;
    int doors;
    int engines;
};

#endif // VEHICLES_H

#ifndef PLANE_H
#define PLANE_H
#include <string>

using namespace std;


class plane{
public:
    plane();
    plane(string temp, int drs, int eng);
    void print();
    bool equal(plane temp);
    string manuf;
    int doors;
    int engines;
};

#endif // PLANE_H

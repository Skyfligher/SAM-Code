#ifndef CAR_H
#define CAR_H
#include <string>

using namespace std;


class car{
public:
    car();
    car(string temp, int drs);
    void print();
    bool equal(car temp);
    string manuf;
    int doors;
};
#endif // CAR_H

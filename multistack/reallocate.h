#ifndef REALLOCATE_H
#define REALLOCATE_H
#include <math.h>

template<class myType>

class reallocate
{
public:
   // reallocate();
    reallocate(myType temp);
    void movestack(myType *temp2);
    int availspace;
    int totgrow;
    int j;
    int *mainarray;
    float equalallocate = .13;
    float growthallocate = .87;
    float alpha;
    float beta;
    float sigma;
    float tau;
    int delta;
};
#endif // REALLOCATE_H

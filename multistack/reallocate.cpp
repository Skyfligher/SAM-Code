#include "reallocate.h"

template<class myType>
reallocate<myType>::reallocate(myType temp)
{
    availspace = temp.m-temp.l0;
    totgrow = 0;
    j = temp.n;

    if(availspace = 0){
        cout<<"Error, out of space.";
        return 0;
    }

    mainarray = new int[temp.n+1];
    for(int i = 0; i<temp.n;i++){
        mainarray[i] = temp.top[i];
    }

    /////////////////////////////////////////////////////////
    for(int i = 0; j>i ;j--){
        availspace = availspace - (temp.top[j]-temp.base[j]);
        if(temp.top[j] > oldtop[j]){
            mainarray[j+1] = temp.top[j]-mainarray[j];
            totgrow = totgrow + mainarray[j+1];
        }
        else{
            growth[j] = 0;
        }
    }

    /////////////////////////////////////////////////////////
    alpha = (equalallocate * availspace)/temp.n;
    beta = ((growthallocate * availspace)/totgrow);

    /////////////////////////////////////////////////////////
    mainarray[1] = temp.base[1];
    sigma = 0;

    for(j=2;j <= temp.n;j++){
        tau = sigma + alpha + growth[j-1] * beta;
        mainarray[j] = mainarray[j-1] + (temp.top[j-1]-temp.base[j-1]) + floor(tau) - floor(sigma);
        sigma = tau;
    }

    /////////////////////////////////////////////////////////
    temp.top[temp.k] = temp.top[temp.k]-1;
    movestack(*temp);
    temp.top[temp.k] = temp.top[temp.k]+1;
    temp.top[temp.k] = temp.temp;


}

template<class myType>
void reallocate<myType>::movestack(myType *temp2){

    for(j=2; j<= temp2.n;j++){
        delta = temp2.base[j]-mainarray[j];
        for(int l = (temp2.base[j]+1); (temp2.base[j]+2) <= temp2.top[j];l--){
            temp2.mem[l-delta] = temp2.mem[l];
        }
        temp2.base[j] = mainarray[j];
        temp2.top[j] = temp2.top[j]-delta;
    }


    for(j = temp2.n; j >= 2; j--){
        if(mainarray[j]>temp2.base[j]){
            delta = mainarray[j]-temp2.base[j];
            for(int l = temp2.top[j];(temp2.top[j]-1) <= (temp2.base[j]+1);l--){
                temp2.mem[l+delta] = temp2.mem[l];
            }
            temp2.base[j] = mainarray[j];
            temp2.top[j] = temp2.top[j]+delta;
        }
    }
}
template class reallocate<stack>;

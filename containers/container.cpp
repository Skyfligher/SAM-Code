#include "container.h"

template <class myType,class myType2>

container<myType, myType2>::container()
{

}


template <class myType,class myType2>

bool container<myType,myType2>::equals(container M){
    if(this->equals(M)){
        return true;
    }
    else{
        return false;
    }
}


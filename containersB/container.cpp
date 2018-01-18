#include "container.h"
#include <car.h>
#include <plane.h>
#include <list.h>

template <class myType>
container<myType>::container()
{

}

template<class myType>
container<myType>::container(myType){

}

template <class myType>
bool container<myType>::equals(container temp){
    if(this->equals(temp)){
        return true;
    }
    else{
        return false;
    }
}

template class container<car>;
template class container<plane>;

template class list<container<plane>>;
template class list<container<car>>;

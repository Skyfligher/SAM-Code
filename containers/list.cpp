#include "list.h"

template<class myType>
list<myType>::list()
{
    listhead.head = *listhead;
    listhead.tail = *listhead;
}

template<class myType>
list<myType>::list(myType temp){
    length++;

    temp.head = *listhead;
    temp.tail = *listhead;

    listhead.head = *temp;
    listhead.tail = *temp;
}

template<class myType>
myType list<myType>::get(int position){
    myType *next = listhead.tail;
    for(int i = 1; i<position;i++){
        next = &next.tail;
    }
    return &next;
}

//////////////////////////////Insert/////////////////////////////////
template<class myType>
void list<myType>::insert(myType temp){
    myType *next = listhead.tail;
    for(int i = 1; i<length;i++){
        next = &next.tail;
    }
    &next.tail = *temp;
    temp.head = next;
    temp.tail = *listhead;
    length++;

}

////////////////////////////////Search///////////////////////////////
template<class myType>
int list<myType>::search(myType temp){
    myType *next = listhead.tail;
    if(this->empty()){
        return 0;
    }
    else{
        for(int i = 1; i<length;i++){
            if(&next = temp){
                return i;
            }
            else{
                next = &next.tail;
            }
        }
        return -1;
    }
}

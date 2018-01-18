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

//////////////////////////////Empty Check///////////////////
template<class myType>
bool list<myType>::isempty(){
    if(listhead.tail = listhead.head){
        return true;
    }
    else{
        return false;
    }
}

///////////////////////////////Insert////////////////////////
template<class myType>
void list<myType>::insert(myType temp){
    myType *next = listhead.tail;
    next.head = *temp;
    temp.tail = next;
    listhead.tail = *temp;
    temp.head = *listhead;
    length++;
}

//////////////////////////////Insert Rear////////////////////
template<class myType>
void list<myType>::insertRear(myType temp){
    myType *next = listhead.tail;
    for(int i = 1; i<length; i++){
        next = &next.tail;
    }
    &next.tail = *temp;
    temp.head = next;
    temp.tail = *listhead;
    length++;
}

//////////////////////////////Remove/////////////////////////
template<class myType>
void list<myType>::remove(int position){
    myType *nhead;
    myType *ntail;
    myType *next = listhead.tail;

    if(!this->isempty()){
        for(int i = 1; i<position; i++){
            next = &next.tail;
        }
        nhead = &next.head;
        ntail = &next.tail;

        &nhead.tail = ntail;
        &ntail.head = nhead;
    }
}

//////////////////////////////Search/////////////////////////
template<class myType>
int list<myType>::search(myType temp){
    myType *next = listhead.tail;
    if(this->isempty()){
        return 0;
    }
    else{
        for(int i = 1; i<length; i++){
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

//////////////////////////////Print List///////////////////////
template<class myType>
void list<myType>::print(){
    myType *next = listhead.tail;
    if(this->isempty()){
        return;
    }
    else{
        next.print();
        for(int i = 1; i<length; i++){
            next = &next.tail;
            next.print();
        }
    }
    return;
}



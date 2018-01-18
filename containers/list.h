#ifndef LIST_H
#define LIST_H

template<class myType>

class list
{
public:
    int length = 0;
    myType listhead = new myType();
    list();
    list(myType temp);
    void insert(myType temp);
    void remove();
    myType get();
    int search(myType temp);

};

#endif // LIST_H

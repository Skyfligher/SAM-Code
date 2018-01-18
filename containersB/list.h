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
    bool isempty();
    void insert(myType temp);
    void insertRear(myType temp);
    void remove(int position);
    int search(myType temp);
    void print();
};

#endif // LIST_H

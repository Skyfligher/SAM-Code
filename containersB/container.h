#ifndef CONTAINER_H
#define CONTAINER_H


template <class myType>

class container:myType
{
public:
    container(myType);
    container();
    container *head;
    container *tail;
    bool equals(container temp);


};


#endif // CONTAINER_H

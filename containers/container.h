#ifndef CONTAINER_H
#define CONTAINER_H

template <class myType,class myType2>

class container:myType,myType2
{
public:
    container();
    container *head;
    container *tail;
    bool equals(container M);
};


#endif // CONTAINER_H

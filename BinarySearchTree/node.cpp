#include "node.h"



node::node(){
    lthread = NULL;
    rthread = NULL;
    lvalue = NULL;
    rvalue = NULL;
    name = "";
    number = "";
}
node::node(string temp1,string temp2)
{
    name = temp1;
    number = temp2;
    lvalue = NULL;
    rvalue = NULL;
}
bool node::operator==(node temp){
    if(this->name == temp.name){
        return true;
    }
    else{
        return false;
    }
}
bool node::operator<(node temp){
    if(this->name < temp.name){
        return true;
    }
    else{
        return false;
    }
}
bool node::operator>(node temp){
    if(this->name > temp.name){
        return true;
    }
    else{
        return false;
    }
}
void node::operator=(node temp){
    this->lthread = temp.lthread;
    this->lvalue = temp.lvalue;
    this->rthread = temp.rthread;
    this->rvalue = temp.rvalue;
    this->name = temp.name;
    this->number = temp.number;
}


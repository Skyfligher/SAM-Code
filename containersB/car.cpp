#include "car.h"
#include <string>
#include <iostream>


car::car(){
    manuf = " ";
    doors = 0;
}
car::car(string temp, int drs){
    manuf = temp;
    doors = drs;
}
void car::print(){
    cout<<manuf<<" "<<doors<<" doors\n";
}
bool car::equal(car temp){
    if(manuf == temp.manuf && doors == temp.doors){
        return true;
    }
    else{
        return false;
    }
}

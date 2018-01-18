#include "vehicles.h"
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
    cout<<manuf<<" "<<doors<<" doors";
}


plane::plane(){
    manuf = " ";
    doors = 0;
    engines = 0;
}
plane::plane(string temp, int drs, int eng){
    manuf = temp;
    doors = drs;
    engines = eng;
}
void plane::print(){
    cout<<manuf<<" "<<doors<<" doors, "<<engines<<" engines";
}


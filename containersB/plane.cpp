#include "plane.h"
#include <string>
#include <iostream>


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
    cout<<manuf<<" "<<doors<<" doors, "<<engines<<" engines\n";
}
bool plane::equal(plane temp){
    if(manuf == temp.manuf && doors == temp.doors && engines == temp.engines){
        return true;
    }
    else{
        return false;
    }
}

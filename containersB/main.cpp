#include <list>
#include <container.h>
#include <string>
#include <car.h>
#include <plane.h>
#include <iostream>


container<plane> plane1 = plane("Boeing",3,6);
container<plane> plane2 = plane("Piper",2,1);
container<plane> plane3 = plane("Cessna", 4,4);

container<car> car1 = car("Ford",4);
container<car> car2 = car("Ford",2);
container<car> car3 = car("GMC",2);
container<car> car4 = car("RAM",2);
container<car> car5 = car("Chevy",3);

list<container<plane>> planes;
list<container<car>> cars;

using namespace std;

int main()
{
cars.insertRear(car1);
cars.insert(car2);
cars.insertRear(car3);
cars.insertRear(car4);
cars.insert(car5);

cout<<cars.length<<"\n\n";
cars.print();
cout<<"\n\n";

planes.insert(plane1);
planes.insert(plane2);
planes.insert(plane3);

planes.print();
}

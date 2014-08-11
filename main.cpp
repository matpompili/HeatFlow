#include <iostream>
#include "Grid.hpp"

int main() {
  Grid *linTest = new Grid(20, 1.);
  linTest->setAllTemperatures(300.);
  linTest->setTemperature(0, 330.);
  //linTest->setFixed(0, true);
  linTest->setTemperature(19, 270.);
  //linTest->setFixed(19, true);
  //linTest->setFixed(5,true);
  double dt = 0.01;
  int count = 0;
  while (count<1000) {
    for(int i = 0; i < 20; i++) {
      std::cout << i << " " << linTest->getTemperature(i) << std::endl;
    }
    std::cout << std::endl;
    for(size_t i = 0; i < 20; i++)
    {
      linTest->nextStep(dt);
    }
    count++;
  }
}

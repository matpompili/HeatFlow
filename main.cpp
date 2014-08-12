#include <iostream>
#include "Grid.hpp"

int main() {
  Grid *linTest = new Grid(20, 1.);
  linTest->setAllTemperatures(300.);
  for(int i = 0; i < 20; i++)
  {
    linTest->setTemperature(i, 0, 330.);
    linTest->setFixed(i, 0, true);
  }
  for(int i = 0; i < 20; i++)
  {
    linTest->setTemperature(i, 19, 270.);
    linTest->setFixed(i, 19, true);
  }
  //linTest->setFixed(19, true);
  //linTest->setFixed(5,true);
  double dt = 0.01;
  int count = 0;
  while (count < 50) {
    for(int i = 0; i < 20; i++) {
      for(int j = 0; j < 20; j++) {
        std::cout << linTest->getTemperature(19-i, j) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    for(size_t i = 0; i < 200; i++)
    {
      linTest->nextStep(dt);
    }
    count++;
  }
}

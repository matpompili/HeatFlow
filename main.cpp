#include <iostream>
#include "Grid.hpp"

int main() {
  Grid *linTest = new Grid(20, 1.);
  linTest->setAllTemperatures(300.);
  linTest->setTemperature(0, 330.);
  linTest->setFixed(0, true);
  linTest->setTemperature(19, 270.);
  linTest->setFixed(19, true);
  double dt = 0.1;
  while (true) {
    for(int i = 0; i < 20; i++) {
      std::cout << linTest->getTemperature(i) << " ";
    }
    std::cout << std::endl;
    linTest->nextStep(dt);
  }
}

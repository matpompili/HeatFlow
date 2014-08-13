#include <iostream>
#include "Grid.hpp"
#include "Function.hpp"
#include <cmath>

int main() {
  Grid *linTest = new Grid(20, 1.);
  linTest->setAllTemperatures(300.);
  linTest->setAllAlfas(3);
  // for(int i = 0; i < 20; i++)
  // {
  //   linTest->setTemperature(i, 0, 330.);
  //   linTest->setFixed(i, 0, true);
  // }
  // for(int i = 0; i < 20; i++)
  // {
  //   linTest->setTemperature(i, 19, 270.);
  //   linTest->setFixed(i, 19, true);
  // }

  Function *func1 = new Function(.1, 30, 0, 300);

  linTest->setTemperatureFunc(10,10, func1);
  linTest->setTemperatureFunc(2,2, func1);

  Function *func2 = new Function(.05, 30, M_PI, 300);

  linTest->setTemperatureFunc(15,15, func2);
  //linTest->setTemperature(10, 10, 250.);
  //linTest->setFixed(10, 10, true);
  //linTest->setFixed(19, true);
  //linTest->setFixed(5,true);
  double dt = 0.01;
  int count = 0;
  while (count < 1000) {
    for(int i = 0; i < 20; i++) {
      for(int j = 0; j < 20; j++) {
        std::cout << linTest->getTemperature(19-i, j) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    for(size_t i = 0; i < 50; i++){
      linTest->nextStep(dt);
    }
    count++;
  }
}

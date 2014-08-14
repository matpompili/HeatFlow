#include <iostream>
#include "HeatFlowGrid.hpp"
#include "HeatFlowFunction.hpp"
#include <cmath>

int main(int argc, char** argv) {
  HeatFlowGrid *linTest = new HeatFlowGrid(atoi(argv[1]), atoi(argv[2]), atof(argv[3]));
  linTest->setAllTemperatures(300.);
  linTest->setAllAlfas(2.3E-5); //Iron
  linTest->setTemperature(5,3,350.);
  linTest->setFixed(5,3,true);
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

  HeatFlowFunction *func1 = new HeatFlowFunction(.05, 20, 0, 310);
  linTest->setTemperatureFunc(10,10, func1);
  HeatFlowFunction *func2 = new HeatFlowFunction(.1, 10, M_PI, 320);
  linTest->setTemperatureFunc(15,15, func2);
  //linTest->setTemperature(10, 10, 250.);
  //linTest->setFixed(10, 10, true);
  //linTest->setFixed(19, true);
  //linTest->setFixed(5,true);
  double dt = atof(argv[5]);
  double endTime = atof(argv[4]);
  double t = 0.;
  int rate = ceil(endTime/dt/atof(argv[6]));
  int steps = 0;
  while (t < endTime) {
    if(steps % rate == 0) {
      linTest->printGrid();
    }
    linTest->nextStep(dt);
    steps++;
    t += dt;
  }
  FILE* plotScript = fopen("plots/plot_script", "w");
  fprintf(plotScript, ""
  "set terminal png\n"
  "set pm3d map\n"
  "set pm3d interpolate 0,0\n"
  "set cbrange [290:350]\n"
  "do for [i=0:%d] {\n"
  "  set output sprintf('plots/pngs/HeatMap%%03.0f.png',i)\n"
  "  set title sprintf(\"t=%%f\",i*%f)\n"
  "  splot 'plots/HeatMap.plot' index i matrix\n"
  "}\n", atoi(argv[6]), rate*dt);
  fclose(plotScript);
  exit(EXIT_SUCCESS);
}

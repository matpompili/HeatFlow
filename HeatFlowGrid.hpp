#ifndef __HEATFLOWGRID_HPP__
#define __HEATFLOWGRID_HPP__

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include "HeatFlowFunction.hpp"

typedef struct {
  double temperature, laplacian, alfa;
  bool fixed, func;
  //fPtrType tFunction;
  HeatFlowFunction *tFunction;
} Cell;

class HeatFlowGrid {
public:
  HeatFlowGrid(int sizex, int sizey, double lenghtx);
  ~HeatFlowGrid();

  void nextStep(double dt);
  void printGrid();

  void setTemperature(int i, int j, double t);
  void setTemperature(double x, double y, double t);
  void setAllTemperatures(double t);
  void setFixed(int i, int j, bool f);
  void setFixed(double x, double y, bool f);
  void setAllFixed(bool f);

  void setAllAlfas(double a);

  void setTemperatureFunc(int i, int j, HeatFlowFunction *tf);

  double getTemperature(int i, int j);
  double getTemperature(double x, double y);
  double getLaplacian(int i, int j);
  double getLaplacian(double x, double y);
  bool getFixed(int i, int j);
  bool getFixed(double x, double y);
  //double getLinearTemperature(double pos);
  //double gettLinearLaplacian(double pos);
  int getSizeX() {return (int)_sizex;}
  int getSizeY() {return (int)_sizey;}
  double getStep() {return _step;}



private:
  Cell* _cell;
  double _step, _time;
  unsigned int _sizex, _sizey;
  bool _allocated;

  int cellFromPos (double pos);
  double posFromCell (int cell);
  void evaluateLaplacian();
  Cell* getCell(int i, int j);
};
#endif

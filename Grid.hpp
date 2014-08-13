#ifndef __GRID_HPP__
#define __GRID_HPP__

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include "Function.hpp"

typedef double (*fPtrType)(double);

typedef struct {
  double temperature, lagrange, alfa;
  bool fixed, func;
  Function *tFunction;
} Cell;

class Grid {
public:
  Grid(int size, double lenght);
  ~Grid();

  void nextStep(double dt);
  void printGrid();

  void setTemperature(int i, int j, double t);
  void setTemperature(double x, double y, double t);
  void setAllTemperatures(double t);
  void setFixed(int i, int j, bool f);
  void setFixed(double x, double y, bool f);
  void setAllFixed(bool f);

  void setAllAlfas(double a);

  void setTemperatureFunc(int i, int j, Function *tf);

  double getTemperature(int i, int j);
  double getTemperature(double x, double y);
  double getLagrangian(int i, int j);
  double getLagrangian(double x, double y);
  bool getFixed(int i, int j);
  bool getFixed(double x, double y);
  //double getLinearTemperature(double pos);
  //double gettLinearLagrangian(double pos);
  int getSize() {return (int)_size;}
  double getStep() {return _step;}



private:
  Cell* _cell;
  double _step, _time;
  unsigned int _size;
  bool _allocated;

  int cellFromPos (double pos);
  double posFromCell (int cell);
  void fixBounds();
  void evaluateLagrangian();
  Cell* getCell(int i, int j);
};
#endif

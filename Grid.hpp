#ifndef __GRID_HPP__
#define __GRID_HPP__

#include <iostream>
#include <stdlib.h>
#include <cmath>

typedef struct {
  double temperature, lagrange, alfa;
  bool fixed;
} Cell;

class Grid {
public:
  Grid(int size, double lenght);
  ~Grid();

  void nextStep(double dt);

  void setTemperature(int i, int j, double t);
  void setTemperature(double x, double y, double t);
  void setAllTemperatures(double t);
  void setFixed(int i, int j, bool f);
  void setFixed(double x, double y, bool f);
  void setAllFixed(bool f);

  double getTemperature(int i, int j);
  double getTemperature(double x, double y);
  double getLagrangian(int i, int j);
  double getLagrangian(double x, double y);
  bool getFixed(int i, int j);
  bool getFixed(double x, double y);
  //double getLinearTemperature(double pos);
  //double getLinearLagrangian(double pos);
  int getSize() {return (int)_size;}
  double getStep() {return _step;}



private:
  Cell* _cell;
  //double *_values, *_lagrange, _step;
  double _step;
  unsigned int _size;
  //bool _allocated, *_fixed;
  bool _allocated;

  int cellFromPos (double pos);
  double posFromCell (int cell);
  void fixBounds();
  void evaluateLagrangian();
  Cell* getCell(int i, int j);
};
#endif

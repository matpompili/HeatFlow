#ifndef __GRID_H__
#define __GRID_H__

#include <iostream>
#include <cmath>

class Grid {
public:
  Grid(int size, double lenght);
  ~Grid();

  void nextStep(double dt);

  void setTemperature(int cell, double t);
  void setTemperature(double pos, double t);
  void setAllTemperatures(double t);
  void setFixed(int cell, bool f);
  void setFixed(double pos, bool f);
  void setAllFixed(bool f);

  double getTemperature(int cell);
  double getTemperature(double pos);
  double getLagrangian(int cell);
  double getLagrangian(double pos);
  bool getFixed(int cell);
  bool getFixed(double pos);
  //double getLinearTemperature(double pos);
  //double getLinearLagrangian(double pos);
  int getSize() {return (int)_size;}
  double getStep() {return _step;}

private:
  double *_values, *_lagrange, _step;
  unsigned int _size;
  bool _allocated, *_fixed;

  int cellFromPos (double pos);
  double posFromCell (int cell);
  void fixBounds();
  void evaluateLagrangian();
};
#endif

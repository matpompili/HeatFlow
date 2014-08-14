#ifndef __HEATFLOWFUNCTION_HPP__
#define __HEATFLOWFUNCTION_HPP__

#include <cmath>

class HeatFlowFunction {
public:
  HeatFlowFunction(double f, double a, double p, double o);
  double Oscillator(double t);
private:
  double _frequency, _amplitude, _phase, _offset;
};

#endif

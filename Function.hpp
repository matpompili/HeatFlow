#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include <cmath>

class Function {
public:
  Function(double f, double a, double p, double o);
  double Oscillator(double t);
private:
  double _frequency, _amplitude, _phase, _offset;
};

#endif

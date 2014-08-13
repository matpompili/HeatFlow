#include "Function.hpp"

Function::Function(double f, double a, double p, double o) {
  _frequency = f;
  _amplitude = a;
  _phase = p;
  _offset = o;
}

double Function::Oscillator(double t) {
  return _amplitude * sin(2.*M_PI*_frequency*t + _phase) + _offset;
}

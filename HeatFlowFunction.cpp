#include "HeatFlowFunction.hpp"

HeatFlowFunction::HeatFlowFunction(double f, double a, double p, double o) {
  _frequency = f;
  _amplitude = a;
  _phase = p;
  _offset = o;
}

double HeatFlowFunction::Oscillator(double t) {
  return _amplitude * sin(2.*M_PI*_frequency*t + _phase) + _offset;
}

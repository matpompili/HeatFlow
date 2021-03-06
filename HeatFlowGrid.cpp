#include "HeatFlowGrid.hpp"

using namespace std;

HeatFlowGrid::HeatFlowGrid(int sizex, int sizey, double lenghtx) {
  if ((sizex * sizey == 0) || (lenghtx == 0)) {
    //TODO: EXIT HERE AND ERROR
  }
  _sizex = abs(sizex);
  _sizey = abs(sizey);
  _step = lenghtx / (double) _sizex;
  _time = 0.;
  _cell = (Cell*) calloc(_sizex * _sizey, sizeof(Cell));
  if(_cell != NULL) {
    _allocated = true;
  } else {
    _allocated = false;
    //TODO: EXIT HERE AND ERROR
  }
}

HeatFlowGrid::~HeatFlowGrid() {
  if(_allocated) {
    free(_cell);
  }
}

void HeatFlowGrid::nextStep(double dt) {
  dt = fabs(dt);
  _time += dt;
  this->evaluateLaplacian();
  double tTemp;
  for(int i = 0; i < _sizex; i++) {
    for(int j = 0; j < _sizey; j++) {
      if(!this->getCell(i,j)->fixed){
        tTemp  = this->getCell(i,j)->temperature;
        tTemp += dt*this->getCell(i,j)->alfa*this->getCell(i,j)->laplacian;
        this->getCell(i,j)->temperature = tTemp;
      } else if (this->getCell(i,j)->func) {
        double value = this->getCell(i,j)->tFunction->Oscillator(_time);
        this->getCell(i,j)->temperature = value;
      }
    }
  }
}

void HeatFlowGrid::printGrid(){
  for(int j = 0; j < _sizey; j++) {
    for(int i = 0; i < _sizex; i++) {
      std::cout << this->getTemperature(i, _sizey-1-j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void HeatFlowGrid::setTemperature(int i, int j, double t) {
  this->getCell(i,j)->temperature = fabs(t);
}

void HeatFlowGrid::setTemperature(double x, double y, double t) {
  this->setTemperature(cellFromPos(x), cellFromPos(y), t);
}

void HeatFlowGrid::setAllTemperatures(double t) {
  t = fabs(t);
  for(int i = 0; i < _sizex; i++) {
    for(int j = 0; j < _sizey; j++) {
      this->getCell(i,j)->temperature = t;
    }
  }
}

void HeatFlowGrid::setFixed(int i, int j, bool f) {
  this->getCell(i,j)->fixed = f;
}

void HeatFlowGrid::setFixed(double x, double y, bool f) {
  this->setFixed(cellFromPos(x), cellFromPos(y), f);
}

void HeatFlowGrid::setAllFixed(bool f) {
  for(int i = 0; i < _sizex; i++) {
    for(int j = 0; j < _sizey; j++) {
      this->getCell(i,j)->fixed = f;
    }
  }
}

void HeatFlowGrid::setAllAlfas(double a) {
  for(int i = 0; i < _sizex; i++) {
    for(int j = 0; j < _sizey; j++) {
      this->getCell(i,j)->alfa = a;
    }
  }
}

void HeatFlowGrid::setTemperatureFunc(int i, int j, HeatFlowFunction *tf) {
  this->getCell(i,j)->tFunction = tf;
  this->getCell(i,j)->func = (tf==NULL)?false:true;
  this->getCell(i,j)->fixed = (tf==NULL)?false:true;
  if (tf==NULL) {
    std::fprintf(stderr, "No func setted\n");
  }
}

double HeatFlowGrid::getTemperature(int i, int j) {
  return this->getCell(i,j)->temperature;
}

double HeatFlowGrid::getTemperature(double x, double y) {
  return this->getTemperature(cellFromPos(x), cellFromPos(y));
}

double HeatFlowGrid::getLaplacian(int i, int j) {
  return this->getCell(i,j)->laplacian;
}

double HeatFlowGrid::getLaplacian(double x, double y) {
  return this->getLaplacian(cellFromPos(x), cellFromPos(y));
}

bool HeatFlowGrid::getFixed(int i, int j) {
  return this->getCell(i,j)->fixed;
}

bool HeatFlowGrid::getFixed(double x, double y) {
  return this->getFixed(cellFromPos(x), cellFromPos(y));
}

int HeatFlowGrid::cellFromPos(double pos) {
  return floor(pos/_step);
}

double HeatFlowGrid::posFromCell (int cell) {
  return cell*_step + _step/2.;
}

void HeatFlowGrid::evaluateLaplacian() { //https://en.wikipedia.org/wiki/Finite_difference#Higher-order_differences
  double tempLagr;
  for(int j = 0; j < _sizey; j++) {//d2x + d2y
    for(int i = 0; i < _sizex; i++) {
      tempLagr = -5.*this->getCell(i, j)->temperature;
      tempLagr += 4./3. * (this->getCell(i-1,j)->temperature + this->getCell(i+1,j)->temperature);
      tempLagr += -1./12. * (this->getCell(i-2,j)->temperature + this->getCell(i+2,j)->temperature);
      tempLagr += 4./3. * (this->getCell(i,j-1)->temperature + this->getCell(i,j+1)->temperature);
      tempLagr += -1./12. * (this->getCell(i,j-2)->temperature + this->getCell(i,j+2)->temperature);
      this->getCell(i,j)->laplacian = tempLagr / pow(_step, 2.);
    }
  }
}

Cell* HeatFlowGrid::getCell(int i, int j) {
  if ((i>=0 && i<_sizex)&&(j>=0 && j<_sizey)) {
    return (_cell + _sizex * j + i);
  } else if (i<0) {
    return this->getCell(0,j);
  } else if (i>=_sizex) {
    return this->getCell(_sizex-1,j);
  } else if (j<0) {
    return this->getCell(i,0);
  } else /*(j>=_sizey)*/ { // should be the only alternative
    return this->getCell(i,_sizey-1);
  }
}

#include "Grid.hpp"

using namespace std;

Grid::Grid(int size, double lenght) {
  if ((size == 0) || (lenght == 0)) {
    //TODO: EXIT HERE AND ERROR
  }
  _size = abs(size);
  _step = lenght / size;
  _cell = (Cell*) calloc(_size * _size, sizeof(Cell));
  //_values = (double*) calloc(_size + 2, sizeof(double));
  //_lagrange = (double*) calloc(_size + 2, sizeof(double));
  //_fixed = (bool*) calloc(_size + 2, sizeof(bool));
  //if((_values != NULL) && (_lagrange != NULL) && (_fixed != NULL)) {
  if(_cell != NULL) {
    _allocated = true;
  } else {
    _allocated = false;
    //TODO: EXIT HERE AND ERROR
  }
}

Grid::~Grid() {
  if(_allocated) {
    //free(_values);
    //free(_lagrange);
    //free(_fixed);
    free(_cell);
  }
}

void Grid::nextStep(double dt) {
  this->evaluateLagrangian();
  double tTemp;
  for(int i = 0; i < _size; i++) {
    for(int j = 0; j < _size; j++) {
      if(!this->getCell(i,j)->fixed){
        tTemp  = this->getCell(i,j)->temperature;
        tTemp += dt*this->getCell(i,j)->lagrange;
        getCell(i,j)->temperature = tTemp;
      }
    }
  }
}

void Grid::setTemperature(int i, int j, double t) {
  this->getCell(i,j)->temperature = fabs(t);
  this->fixBounds();
}

void Grid::setTemperature(double x, double y, double t) {
  this->setTemperature(cellFromPos(x), cellFromPos(y), t);
  //this->setTemperature(cellFromPos(pos), t);
}

void Grid::setAllTemperatures(double t) {
  t = fabs(t);
  for(int i = 0; i < _size; i++) {
    for(int j = 0; j < _size; j++) {
      this->getCell(i,j)->temperature = t;
    }
  }
  this->fixBounds();
}

void Grid::setFixed(int i, int j, bool f) {
  this->getCell(i,j)->fixed = f;
}

void Grid::setFixed(double x, double y, bool f) {
  this->setFixed(cellFromPos(x), cellFromPos(y), f);
}

void Grid::setAllFixed(bool f) {
  for(int i = 0; i < _size; i++) {
    for(int j = 0; j < _size; j++) {
      this->getCell(i,j)->fixed = f;
    }
  }
}

double Grid::getTemperature(int i, int j) {
  return this->getCell(i,j)->temperature;
}

double Grid::getTemperature(double x, double y) {
  return this->getTemperature(cellFromPos(x), cellFromPos(y));
}

double Grid::getLagrangian(int i, int j) {
  return this->getCell(i,j)->lagrange;
}

double Grid::getLagrangian(double x, double y) {
  return this->getLagrangian(cellFromPos(x), cellFromPos(y));
}

bool Grid::getFixed(int i, int j) {
  return this->getCell(i,j)->fixed;
}

bool Grid::getFixed(double x, double y) {
  return this->getFixed(cellFromPos(x), cellFromPos(y));
}

int Grid::cellFromPos(double pos) {
  return floor(pos/_step);
}

double Grid::posFromCell (int cell) {
  return cell*_step + _step/2.;
}

void Grid::fixBounds() {
  // for(size_t i = 0; i < _size; ++) {
  //
  // }
  // _cell->temperature = (_cell + 1)->temperature;
  // (_cell + _size + 1)->temperature = (_cell + _size)->temperature;
}

void Grid::evaluateLagrangian() {
  double tempLagr;
  for(int j = 0; j < _size; j++) {//Nabla X
    for(int i = 0; i < _size; i++) {
      if (i == 0) { //left border -- forward
        tempLagr  = this->getCell(i+2, j)->temperature;
        tempLagr -= 2.*this->getCell(i+1, j)->temperature;
        tempLagr += this->getCell(i, j)->temperature;
      } else if (i == _size-1) { //right border -- backward
        //TODO: Check Math!
        tempLagr  = this->getCell(i, j)->temperature;
        tempLagr -= 2.*this->getCell(i-1, j)->temperature;
        tempLagr += this->getCell(i-2, j)->temperature;
      } else { //others -- central
        tempLagr  = this->getCell(i+1, j)->temperature;
        tempLagr -= 2.*this->getCell(i, j)->temperature;
        tempLagr += this->getCell(i-1, j)->temperature;
      }
      this->getCell(i,j)->lagrange = tempLagr;
    }
  }

  for(int i = 0; i < _size; i++) {//Nabla Y
    for(int j = 0; j < _size; j++) {
      if (j == 0) { //bottom border -- forward
        tempLagr  = this->getCell(i, j+2)->temperature;
        tempLagr -= 2.*this->getCell(i, j+1)->temperature;
        tempLagr += this->getCell(i, j)->temperature;
      } else if (j == _size-1) { //upper border -- backward
        //TODO: Check Math!
        tempLagr  = this->getCell(i, j)->temperature;
        tempLagr -= 2.*this->getCell(i, j-1)->temperature;
        tempLagr += this->getCell(i, j-2)->temperature;
      } else { //others -- central
        tempLagr  = this->getCell(i, j+1)->temperature;
        tempLagr -= 2.*this->getCell(i, j)->temperature;
        tempLagr += this->getCell(i, j-1)->temperature;
      }
      this->getCell(i,j)->lagrange += tempLagr;
    }
  }
}

Cell* Grid::getCell(int i, int j) {
  if ((i>=0 && i<_size)&&(j>=0 && j<_size)) {
    return (_cell + _size * j + i);
  } else {
    return NULL;
    //TODO: EXIT HERE AND ERROR
  }

}

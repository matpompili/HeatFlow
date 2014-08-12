#include "Grid.hpp"

using namespace std;

Grid::Grid(int size, double lenght) {
  if ((size == 0) || (lenght == 0)) {
    //TODO: EXIT HERE AND ERROR
  }
  _size = abs(size);
  _step = lenght / size;
  _cell = (Cell*) calloc((_size + 2)*(_size + 2), sizeof(Cell));
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
  for(int cell = 0; cell < _size; cell++) {
    if(!this->getFixed(cell)){
      tTemp  = this->getTemperature(cell);
      tTemp += dt*this->getLagrangian(cell);
      this->setTemperature(cell, tTemp);
    }
  }
}

void Grid::setTemperature(int i, int j, double t) {
  this->getCell(i,j)->temperature = fabs(t);
  this->fixBounds();
}

void Grid::setTemperature(double x, double y, double t) {
  this->setTemperature(cellFromPos(x), cellFromPos(y), t)
  //this->setTemperature(cellFromPos(pos), t);
}

void Grid::setAllTemperatures(double t) {
  t = fabs(t);
  for(size_t i = 0; i < _size; i++) {
    for(size_t j = 0; j < _size; j++) {
      (_cell + i + 1)->temperature = t;
    }
  }
  this->fixBounds();
}

void Grid::setFixed(int cell, bool f) {
  (_cell + cell + 1)->fixed = f;
}

void Grid::setFixed(double pos, bool f) {
  this->setFixed(cellFromPos(pos),f);
}

void Grid::setAllFixed(bool f) {
  for(size_t i = 0; i < _size; i++)
  {
    (_cell + i + 1)->fixed = f;
  }
}

double Grid::getTemperature(int cell) {
  return (_cell + cell + 1)->temperature;
}

double Grid::getTemperature(double pos) {
  return this->getTemperature(cellFromPos(pos));
}

double Grid::getLagrangian(int cell) {
  return (_cell + cell + 1)->lagrange;
}

double Grid::getLagrangian(double pos) {
  return this->getLagrangian(cellFromPos(pos));
}

bool Grid::getFixed(int cell) {
  return (_cell + cell + 1)->fixed;
}

bool Grid::getFixed(double pos) {
  return this->getFixed(cellFromPos(pos));
}

int Grid::cellFromPos(double pos) {
  return floor(pos/_step);
}

double Grid::posFromCell (int cell) {
  return cell*_step + _step/2.;
}

void Grid::fixBounds() {
  _cell->temperature = (_cell + 1)->temperature;
  (_cell + _size + 1)->temperature = (_cell + _size)->temperature;
}

void Grid::evaluateLagrangian() {
  this->fixBounds(); //Just to be sure...
  double tempLagr;
  for(int cell = 0; cell < _size; cell++) {
    tempLagr  = this->getTemperature(cell-1);
    tempLagr -= 2.* this->getTemperature(cell);
    tempLagr += this->getTemperature(cell+1);
    (_cell + cell + 1)->lagrange = tempLagr;
  }
}

Cell* Grid::getCell(int i, int j) {
  if ((j>=-1 && j<?????))
  return (_cell + (_size + 2) * (j + 1) + i + 1);
}

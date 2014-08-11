#include "Grid.h"

Grid::Grid(int size, double lenght) {
  if ((size == 0) || (lenght == 0)) {
    //TODO: EXIT HERE AND ERROR
  }
  _size = abs(size);
  _step = lenght / size;
  _values = (double*) calloc(_size + 2, sizeof(double));
  _lagrange = (double*) calloc(_size + 2, sizeof(double));
  _fixed = (bool*) calloc(_size + 2, sizeof(bool));
  if((_values != NULL) && (_lagrange != NULL) && (_fixed != NULL))
  {
    _allocated = true;
  } else {
    _allocated = false;
    //TODO: EXIT HERE AND ERROR
  }
}

Grid::~Grid() {
  if(_allocated) {
    free(_values);
    free(_lagrange);
    free(_fixed);
  }
}

void Grid::setTemperature(int cell, double t) {
  *(_values + cell + 1) = fabs(t);
  this->fixBounds();
}

void Grid::setTemperature(double pos, double t) {
  this->setTemperature(cellFromPos(pos), t);
}

void Grid::setAllTemperatures(double t) {
  t = fabs(t);
  for(size_t i = 0; i < _size; i++)
  {
    *(_values + i + 1) = t;
  }
  this->fixBounds();
}

void Grid::setFixed(int cell, bool f) {
  *(_fixed + cell + 1) = f;
}

void Grid::setFixed(double pos, bool f) {
  this->setFixed(cellFromPos(pos),f);
}

void Grid::setAllFixed(bool f) {
  for(size_t i = 0; i < _size; i++)
  {
    *(_fixed + i + 1) = f;
  }
}

double Grid::getTemperature(int cell) {
  return *(_values + cell + 1);
}

double Grid::getTemperature(double pos) {
  return this->getTemperature(cellFromPos(pos));
}

double Grid::getLagrangian(int cell) {
  return *(_lagrange + cell + 1);
}

double Grid::getLagrangian(double pos) {
  return this->getLagrangian(cellFromPos(pos));
}

bool Grid::getFixed(int cell) {
  return *(_fixed + cell + 1);
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
  *_values = *(_values + 1);
  *(_values + _size + 1) = *(_values + _size);
}

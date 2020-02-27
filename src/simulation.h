#ifndef SIMULATION_H
#define SIMULATION_H
#include "io.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>

class Simulation {
public:
  Simulation();
  ~Simulation();

  void run(unsigned long rounds);

private:
  void givehands();
  void analysehands();

  std::array<std::array<unsigned char, 10>, 3> hands;
  unsigned int cards[32];
  unsigned long long games;
  std::array<unsigned long, 9> nKindProt;
  std::mt19937 generator;
};

#endif // SIMULATION_H

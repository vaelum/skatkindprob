#ifndef SIMULATION_H
#define SIMULATION_H
#include <iostream>
#include <random>
#include <string>

class Simulation {
 public:
  Simulation(unsigned long rounds);
  ~Simulation();

 private:
  void givehands();
  void analysehands();
  void sorthands();

  void deletehands();

  void status();
  void progressbar(float progress);

  short hands[3][10];
  unsigned long long games;
  long drprot[8];
  std::mt19937 generator;
};

#endif  // SIMULATION_H

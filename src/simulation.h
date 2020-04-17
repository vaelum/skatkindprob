#ifndef SIMULATION_H
#define SIMULATION_H
#include <algorithm>
#include <iostream>
#include <random>
#include <string>

#include "io.h"

// To double check the calculation in proof.h/proof.cpp
// this class simulates a number of skat card games with random
// card distribution and counts which percentage of them
// have n three of a kind
class Simulation {
 public:
  Simulation();
  ~Simulation();

  // runs the simulation with n rounds
  void run(unsigned long rounds);

 private:
  // creates a random shuffle of cards
  void givehands();
  // analysis a shuffle of cards
  void analysehands();

  // The three hands of player 1 to 3.
  // These hands dont use the representation in handtree.h,
  // instead all 32 cards are numbered from 0 - 31
  std::array<std::array<unsigned char, 10>, 3> hands;

  // card array with values 0 - 31 representing the 32
  // skat cards
  unsigned int cards[32];

  unsigned long long games;                // total number of simulated games
  std::array<unsigned long, 9> nKindProt;  // n three of a kind occurrences

  std::mt19937 generator;
};

#endif  // SIMULATION_H

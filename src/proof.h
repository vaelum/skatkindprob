#ifndef PROOF_H
#define PROOF_H
#include "hand_tree.h"
#include "io.h"
#include <future>
#include <gmpxx.h>
#include <iostream>
#include <random>
#include <string>
#include <thread>

class Proof {
public:
  Proof();
  ~Proof();
  void compute(unsigned int numberOfThreads);

private:
  unsigned long calcMultiplicity(Hand &p1, Hand &p2, Hand &p3);
  unsigned long calcN3Kind(Hand &p1, Hand &p2, Hand &p3);
  std::array<mpz_class, 10> computeThread(std::vector<Hand> p1HandsPart);
  std::array<std::vector<unsigned long>, 5> bncLookup;
};

#endif // PROOF_H

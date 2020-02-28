#include "proof.h"

Proof::Proof() {
  bncLookup[4] = std::vector<unsigned long>({1, 4, 6, 4, 1});
  bncLookup[3] = std::vector<unsigned long>({1, 3, 3, 1});
  bncLookup[2] = std::vector<unsigned long>({1, 2, 1});
  bncLookup[1] = std::vector<unsigned long>({1, 1});
  bncLookup[0] = std::vector<unsigned long>({1});
}

Proof::~Proof() {}

void Proof::compute(unsigned int numberOfThreads) {
  std::cout << "Running proof with " << numberOfThreads << " threads..."
            << std::endl;
  HandTree htree;
  mpz_class n3KindOccurrences[9]; // counts number of combinations with 0 - 8
                                  // three of a kind occurences
  std::fill(n3KindOccurrences, n3KindOccurrences + 9, 0);
  mpz_class nGames = 0; // counts total games

  std::vector emptyHandVector = std::vector<Hand>();
  auto p1Hands = htree.getAllHands(emptyHandVector);

  // split the possible hands for the first player to be passed to the threads
  std::vector<std::vector<Hand>> p1HandsPart;
  unsigned int counter;
  unsigned long size = 36;
  for (counter = 0; counter + size < p1Hands.size(); counter += size) {
    p1HandsPart.push_back(std::vector<Hand>(begin(p1Hands) + counter,
                                            begin(p1Hands) + counter + size));
  }
  if (begin(p1Hands) + counter != end(p1Hands)) {
    p1HandsPart.push_back(
        std::vector<Hand>(begin(p1Hands) + counter, end(p1Hands)));
  }

  // run threads
  unsigned int progress = 0;
  io::progressbar(0);
  std::vector<std::future<std::array<mpz_class, 10>>> fut;
  for (auto part : p1HandsPart) {
    fut.push_back(
        std::async(std::launch::async, &Proof::computeThread, this, part));

    if (fut.size() == numberOfThreads) {
      for (unsigned int i = 0; i < fut.size(); i++) {
        std::array<mpz_class, 10> ret = fut.at(i).get();
        for (unsigned int k = 0; k < 9; k++) {
          n3KindOccurrences[k] += ret[k];
        }
        nGames += ret[9];
      }
      progress += numberOfThreads * size;
      io::progressbar((float)progress / (float)p1Hands.size());
      fut.clear();
    }
  }

  for (unsigned int i = 0; i < fut.size(); i++) {
    std::array<mpz_class, 10> ret = fut.at(i).get();
    for (unsigned int k = 0; k < 9; k++) {
      n3KindOccurrences[k] += ret[k];
    }
    nGames += ret[9];
  }

  // output results
  io::progressbar(1.0);
  std::cout << std::endl;
  for (int i = 0; i < 9; i++) {
    std::cout << "probability for game with " << i << " three of a kind: "
              << (mpf_class)(n3KindOccurrences[i] * 100) / (mpf_class)nGames
              << "%" << std::endl;
  }
}

std::array<mpz_class, 10> Proof::computeThread(std::vector<Hand> p1HandsPart) {
  std::vector p1Hand = std::vector<Hand>();
  std::vector p1p2Hand = std::vector<Hand>();

  HandTree htree;
  std::array<mpz_class, 10> ret; // index 0 - 8 count n kind occurrences and
                                 // index 9 counts total number of games
  unsigned long multi;

  std::fill(ret.begin(), ret.end(), 0);

  for (auto p1h : p1HandsPart) {
    p1Hand = std::vector<Hand>({p1h});
    std::vector<Hand> p2Hands = htree.getAllHands(p1Hand);

    for (auto p2h : p2Hands) {
      p1p2Hand = std::vector<Hand>({p1h, p2h});
      std::vector<Hand> p3Hands = htree.getAllHands(p1p2Hand);

      for (auto p3h : p3Hands) {
        multi = this->calcMultiplicity(p1h, p2h, p3h);

        ret[this->calcN3Kind(p1h, p2h, p3h)] += multi;
        ret[9] += multi;
      }
    }
  }
  return ret;
}

unsigned long Proof::calcN3Kind(Hand &p1, Hand &p2, Hand &p3) {
  unsigned long n3Kind = 0;
  for (unsigned int i = 0; i < 8; i++) {
    if (p1[i] >= 3)
      n3Kind++;
    if (p2[i] >= 3)
      n3Kind++;
    if (p3[i] >= 3)
      n3Kind++;
  }

  return n3Kind;
}

unsigned long Proof::calcMultiplicity(Hand &p1, Hand &p2, Hand &p3) {
  Hand left;
  std::fill(begin(left), end(left), 4);

  unsigned long mp = 1;
  for (unsigned int i = 0; i < 8; i++) {
    mp *= bncLookup[left[i]][p1[i]];
    left[i] -= p1[i];
  }
  for (unsigned int i = 0; i < 8; i++) {
    mp *= bncLookup[left[i]][p2[i]];
    left[i] -= p2[i];
  }
  for (unsigned int i = 0; i < 8; i++) {
    mp *= bncLookup[left[i]][p3[i]];
    left[i] -= p3[i];
  }
  for (unsigned int i = 0; i < 8; i++) {
    mp *= bncLookup[left[i]][left[i]];
  }

  return mp;
}

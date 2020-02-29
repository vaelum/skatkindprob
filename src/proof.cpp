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

  Hand emptyHand;
  std::fill(begin(emptyHand), end(emptyHand), 0);
  std::vector<Hand> p1Hands;
  htree.getAllHands(emptyHand, p1Hands);

  // split the possible hands for the first player to be passed to the threads
  std::vector<std::vector<Hand>> p1HandsPart;
  unsigned int counter;
  unsigned long size = p1Hands.size() / numberOfThreads;
  for (counter = 0; counter + size < p1Hands.size(); counter += size) {
    p1HandsPart.push_back(std::vector<Hand>(begin(p1Hands) + counter,
                                            begin(p1Hands) + counter + size));
  }
  if (begin(p1Hands) + counter != end(p1Hands)) {
    p1HandsPart.push_back(
        std::vector<Hand>(begin(p1Hands) + counter, end(p1Hands)));
  }

  // run threads
  std::atomic_store(&progress, 0);
  io::progressbar(0);
  std::vector<std::future<std::array<mpz_class, 10>>> fut;
  for (auto part : p1HandsPart) {
    fut.push_back(
        std::async(std::launch::async, &Proof::computeThread, this, part));
  }

  // wait for a all threads to finish while updating the progress bar
  bool threadsReady = false;
  while (!threadsReady) {
    for (unsigned int i = 0; i < fut.size(); i++) {
      io::progressbar((float)std::atomic_load(&progress) /
                      (float)p1Hands.size());
      std::chrono::system_clock::time_point time_passed =
          std::chrono::system_clock::now() + std::chrono::microseconds(300000);
      if (fut.at(i).wait_until(time_passed) != std::future_status::ready) {
        break;
      }
      threadsReady = true;
    }
  }

  io::progressbar((float)std::atomic_load(&progress) / (float)p1Hands.size());

  // get values form threads
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
  HandTree htree;
  std::array<mpz_class, 10> ret; // index 0 - 8 count n kind occurrences and
                                 // index 9 counts total number of games
  unsigned long multi;

  std::fill(ret.begin(), ret.end(), 0);

  std::vector<Hand> p2Hands;
  std::vector<Hand> p3Hands;

  Hand p1p2sum;

  unsigned int counter = 0;
  for (auto p1h : p1HandsPart) {
    counter++;
    if (counter % 10 == 0)
      std::atomic_fetch_add(&this->progress, 10);

    p2Hands.clear();
    htree.getAllHands(p1h, p2Hands);

    for (auto p2h : p2Hands) {
      for (unsigned int i = 0; i < 8; i++)
        p1p2sum[i] = p1h[i] + p2h[i];
      p3Hands.clear();
      htree.getAllHands(p1p2sum, p3Hands);

      for (auto p3h : p3Hands) {
        multi = this->calcMultiplicity(p1h, p2h, p3h);

        ret[this->calcN3Kind(p1h, p2h, p3h)] += multi;
        ret[9] += multi;
      }
    }
  }
  return ret;
}

unsigned long Proof::calcN3Kind(const Hand &p1h, const Hand &p2h,
                                const Hand &p3h) {
  unsigned long n3Kind = 0;
  for (unsigned int i = 0; i < 8; i++) {
    if (p1h[i] >= 3)
      n3Kind++;
    if (p2h[i] >= 3)
      n3Kind++;
    if (p3h[i] >= 3)
      n3Kind++;
  }

  return n3Kind;
}

unsigned long Proof::calcMultiplicity(const Hand &p1h, const Hand &p2h,
                                      const Hand &p3h) {
  Hand left;
  std::fill(begin(left), end(left), 4);

  unsigned long mp = 1;
  for (unsigned int i = 0; i < 8; i++) {
    mp *= bncLookup[left[i]][p1h[i]];
    left[i] -= p1h[i];
  }
  for (unsigned int i = 0; i < 8; i++) {
    mp *= bncLookup[left[i]][p2h[i]];
    left[i] -= p2h[i];
  }
  for (unsigned int i = 0; i < 8; i++) {
    mp *= bncLookup[left[i]][p3h[i]];
    left[i] -= p3h[i];
  }
  for (unsigned int i = 0; i < 8; i++) {
    mp *= bncLookup[left[i]][left[i]];
  }

  return mp;
}

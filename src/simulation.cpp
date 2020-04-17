#include "simulation.h"

Simulation::Simulation() {
  std::random_device rd;
  generator = std::mt19937{rd()};

  // initialize cards
  for (unsigned int c = 0; c < 32; c++) {
    cards[c] = c;
  }

  std::fill(begin(nKindProt), end(nKindProt), 0);
  games = 0;
}

Simulation::~Simulation() {}

void Simulation::run(unsigned long rounds) {
  std::cout << "Running simulation with " << rounds << " games..." << std::endl;
  io::progressbar(0);
  for (unsigned long i = 0; i < rounds; i++) {
    this->givehands();
    this->analysehands();

    if ((i + 1) % (rounds / 100) == 0) {
      io::progressbar((float)i / (float)rounds);
    }
  }
  io::progressbar(1.0);
  std::cout << std::endl;

  for (unsigned int i = 0; i < 9; i++) {
    std::cout << "probability for game with " << i << " three of a kind :"
              << double(nKindProt[i]) / double(games) * 100.0 << "%"
              << std::endl;
  }
}

void Simulation::givehands() {
  std::shuffle(cards, cards + 32, generator);
  std::copy(cards, cards + 10, begin(hands[0]));
  std::copy(cards + 10, cards + 20, begin(hands[1]));
  std::copy(cards + 20, cards + 30, begin(hands[2]));
}

void Simulation::analysehands() {
  int dcounter = 0;

  // s_array counts how many cards of one symbol are in a hand.
  // As there are 4 cards of each symbol, card % 8
  // gives 8 residue classes representing the 8 card symbols.
  std::array<unsigned char, 8> s_array;

  for (int hand = 0; hand < 3; hand++) {
    std::fill(begin(s_array), end(s_array), 0);

    for (int i = 0; i < 10; i++) {
      s_array[hands[hand][i] % 8]++;
    }
    for (int i = 0; i < 8; i++) {
      if (s_array[i] >= 3) dcounter++;
    }
  }
  this->games++;
  this->nKindProt[dcounter]++;
}

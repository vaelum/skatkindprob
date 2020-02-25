#include "simulation.h"

Simulation::Simulation(unsigned long rounds) {
  std::random_device rd;
  generator = std::mt19937{rd()};
  std::cout << "Simulation with " << rounds << " games..." << std::endl;
  this->progressbar(0);
  for (unsigned long i = 0; i < rounds; i++) {
    this->deletehands();

    this->givehands();

    this->sorthands();

    this->analysehands();

    if ((i + 1) % (rounds / 100) == 0) {
      this->progressbar((float)i / (float)rounds);
    }
  }
  this->progressbar(1.0);
  std::cout << std::endl;
  this->status();
}

Simulation::~Simulation() {}

void Simulation::progressbar(float progress) {
  int barWidth = 70;

  std::cout << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos)
      std::cout << "=";
    else if (i == pos)
      std::cout << ">";
    else
      std::cout << " ";
  }
  std::cout << "] " << int(progress * 100.0) << " %\r";
  std::cout.flush();
}

void Simulation::givehands() {
  short used[30];
  int hused = 0;
  short value = 0;
  bool found = false;
  std::uniform_int_distribution<int> distribution(1, 32);
  for (int i = 0; i < 10; i++) {
    do {
      found = false;
      value = distribution(generator);
      for (int g = 0; g < hused; g++) {
        if (used[g] == value) {
          found = true;
        }
      }
    } while (found);
    hands[0][i] = value;
    used[hused] = value;
    hused++;
  }
  for (int i = 0; i < 10; i++) {
    do {
      found = false;
      value = distribution(generator);
      for (int g = 0; g < hused; g++) {
        if (used[g] == value) {
          found = true;
        }
      }
    } while (found);
    hands[1][i] = value;
    used[hused] = value;
    hused++;
  }
  for (int i = 0; i < 10; i++) {
    do {
      found = false;
      value = distribution(generator);
      for (int g = 0; g < hused; g++) {
        if (used[g] == value) {
          found = true;
        }
      }
    } while (found);
    hands[2][i] = value;
    used[hused] = value;
    hused++;
  }
  return;
}
void Simulation::analysehands() {
  int dcounter = 0;
  for (int hand = 0; hand < 3; hand++) {
    for (int i = 0; i < 7; i++) {
      if (hands[hand][i] == hands[hand][i + 1] - 1 &&
          hands[hand][i + 1] == hands[hand][i + 2] - 1) {
        if (hands[hand][i] == 1 || hands[hand][i] == 2 || hands[hand][i] == 5 ||
            hands[hand][i] == 6 || hands[hand][i] == 9 ||
            hands[hand][i] == 10 || hands[hand][i] == 13 ||
            hands[hand][i] == 14 || hands[hand][i] == 17 ||
            hands[hand][i] == 18 || hands[hand][i] == 21 ||
            hands[hand][i] == 22 || hands[hand][i] == 25 ||
            hands[hand][i] == 26 || hands[hand][i] == 29 ||
            hands[hand][i] == 30) {
          dcounter++;
        }
      }
    }
  }
  games++;
  drprot[dcounter]++;
}
void Simulation::sorthands() {
  short hilf;

  for (short i = 0; i < 3; i++)
    for (short n = 0; n < 9; n++) {
      for (short m = n + 1; m < 10; m++) {
        if (hands[i][n] > hands[i][m]) {
          hilf = hands[i][n];
          hands[i][n] = hands[i][m];
          hands[i][m] = hilf;
        }
      }
    }
}

void Simulation::deletehands() {
  for (int i = 0; i < 3; i++)
    for (int f = 0; f < 10; f++) hands[i][f] = -1;
}

void Simulation::status() {
  std::cout << "probability for game with 0 tok :"
            << double(drprot[0]) / double(games) * 100 << "%" << std::endl;
  std::cout << "probability for game with 1 tok :"
            << double(drprot[1]) / double(games) * 100 << "%" << std::endl;
  std::cout << "probability for game with 2 tok :"
            << double(drprot[2]) / double(games) * 100 << "%" << std::endl;
  std::cout << "probability for game with 3 tok :"
            << double(drprot[3]) / double(games) * 100 << "%" << std::endl;
  std::cout << "probability for game with 4 tok :"
            << double(drprot[4]) / double(games) * 100 << "%" << std::endl;
  std::cout << "probability for game with 5 tok :"
            << double(drprot[5]) / double(games) * 100 << "%" << std::endl;
  std::cout << "probability for game with 6 tok :"
            << double(drprot[6]) / double(games) * 100 << "%" << std::endl;
  std::cout << "probability for game with 7 tok :"
            << double(drprot[7]) / double(games) * 100 << "%" << std::endl;
  std::cout << "probability for 2 tok or more if there is 1 :"
            << double(drprot[2] + drprot[3] + drprot[4] + drprot[5] +
                      drprot[6] + drprot[7]) /
                   double(drprot[1] + drprot[2] + drprot[3] + drprot[4] +
                          drprot[5] + drprot[6] + drprot[7]) *
                   100
            << "%" << std::endl;
  std::cout << "probability for 3 tok or more if there are 2 :"
            << double(drprot[3] + drprot[4] + drprot[5] + drprot[6] +
                      drprot[7]) /
                   double(drprot[2] + drprot[3] + drprot[4] + drprot[5] +
                          drprot[6] + drprot[7]) *
                   100
            << "%" << std::endl;
  std::cout << "probability for 4 tok or more if there are 3 :"
            << double(drprot[4] + drprot[5] + drprot[6] + drprot[7]) /
                   double(drprot[3] + drprot[4] + drprot[5] + drprot[6] +
                          drprot[7]) *
                   100
            << "%" << std::endl;
  std::cout << "probability for 5 tok or more if there are 4 :"
            << double(drprot[5] + drprot[6] + drprot[7]) /
                   double(drprot[4] + drprot[5] + drprot[6] + drprot[7]) * 100
            << "%" << std::endl;
  std::cout << "probability for 6 tok or more if there are 5 :"
            << double(drprot[6] + drprot[7]) /
                   double(drprot[5] + drprot[6] + drprot[7]) * 100
            << "%" << std::endl;
  std::cout << "probability for 7 tok if there are 6 :"
            << double(drprot[7]) / double(drprot[6] + drprot[7]) * 100 << "%"
            << std::endl;
}

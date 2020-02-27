#include "hand_tree.h"
#include "proof.h"
#include "simulation.h"
#include <iostream>

using namespace std;

void help() {
  std::string help = "Created by Jon Amos Fehling in 2020\n"
                     "Usage: skb [Options]\n\n"
                     "Options:\n"
                     "  -s       runs the simulation\n"
                     "  -p       runs the proof\n"
                     "  -sr x    sets rounds of simulation to x\n"
                     "  -pf x    sets threads used by proof to x\n";
  std::cout << help;
  exit(-1);
}

int main(int argc, char *argv[]) {

  std::vector<std::string> strArgv(argv + 1, argv + argc);

  unsigned int index = 0;

  bool runProof = false;
  bool runSimulation = false;
  unsigned int simulationRounds = 10000000;
  unsigned int proofThreads = 12;

  while (index < strArgv.size()) {
    if (strArgv[index] == "-s") {
      runSimulation = true;
      index += 1;
    } else if (strArgv[index] == "-p") {
      runProof = true;
      index += 1;
    } else if (strArgv[index] == "-sr") {
      if (index + 1 >= strArgv.size()) {
        help();
      }
      try {
        simulationRounds = std::stoul(strArgv[index + 1]);
        index += 2;
      } catch (...) {
        help();
      }
    } else if (strArgv[index] == "-pf") {
      if (index + 1 >= strArgv.size()) {
        help();
      }
      try {
        proofThreads = std::stoul(strArgv[index + 1]);
        index += 2;
      } catch (...) {
        help();
      }
    } else {
      help();
    }
  }

  if (!runSimulation && !runProof) {
    help();
  }
  if (runSimulation) {
    Simulation sim;
    sim.run(simulationRounds);
  }
  if (runProof) {
    Proof proof;
    proof.compute(proofThreads);
  }
  return 0;
}

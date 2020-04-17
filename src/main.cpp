#include <iostream>

#include "hand_tree.h"
#include "proof.h"
#include "simulation.h"

using namespace std;

void help() {
  std::string help =
      "Created by Jon Amos Fehling in 2020\n"
      "Usage: skb [Options]\n\n"
      "Options:\n"
      "  -s       runs the simulation\n"
      "  -p       runs the proof\n"
      "  -sr x    sets rounds of simulation to x\n"
      "  -pt x    sets threads used by proof to x\n";
  std::cout << help;
  exit(-1);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> strArgv(argv + 1, argv + argc);

  unsigned int index = 0;

  // set default values
  bool runProof = false;
  bool runSimulation = false;
  unsigned int simulationRounds = 10000000;
  unsigned int proofThreads = 12;

  // evaluate command line input
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
    } else if (strArgv[index] == "-pt") {
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
    auto t1 = std::chrono::high_resolution_clock::now();

    Simulation sim;
    sim.run(simulationRounds);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "\nRuntime: " << duration / 1000000.0 << " seconds"
              << std::endl
              << std::endl;
  }
  if (runProof) {
    auto t1 = std::chrono::high_resolution_clock::now();

    Proof proof;
    proof.compute(proofThreads);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "\nRuntime: " << duration / 1000000.0 << " seconds"
              << std::endl
              << std::endl;
  }
  return 0;
}

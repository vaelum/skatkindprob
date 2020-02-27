#ifndef HAND_TREE_H
#define HAND_TREE_H
#include <array>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

struct Hand {
  unsigned int symbol[8];
  Hand() {
    symbol[0] = 0;
    symbol[1] = 0;
    symbol[2] = 0;
    symbol[3] = 0;
    symbol[4] = 0;
    symbol[5] = 0;
    symbol[6] = 0;
    symbol[7] = 0;
  }
};

struct Leaf {
  std::array<std::shared_ptr<Leaf>, 5> children;
  std::shared_ptr<Leaf> parent;
  unsigned int depth;
  Hand hand;
  Leaf(std::shared_ptr<Leaf> parent, unsigned int depth, Hand hand) {
    this->parent = parent;
    this->depth = depth;
    this->hand = hand;
  }
};

class HandTree {
public:
  HandTree();
  ~HandTree();

  std::vector<Hand> getAllHands(std::vector<Hand> &dealedHands);

private:
  void populate(std::shared_ptr<Leaf> leaf, Hand hand, unsigned int depth);
  bool isValidHand(Hand &hand);
  bool areCompatibleHands(std::vector<Hand> &hands, Hand &h);
  void getAllHandsRec(std::shared_ptr<Leaf> &leaf,
                      std::vector<Hand> &dealedHands,
                      std::vector<Hand> &retHands);

  std::shared_ptr<Leaf> mainLeaf;
};

#endif // HAND_TREE_H

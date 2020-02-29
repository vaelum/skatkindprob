#ifndef HAND_TREE_H
#define HAND_TREE_H
#include <array>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>

// data structure representing a subsets of the 32 skat cards.
// Hand[n] can have values from 0 - 4 representing how many cards of a.e.
// symbol king are in a subset
typedef std::array<unsigned int, 8> Hand;

// HandTree is a tree data structure using Leaf as nodes.
// HandTree contains all allowed hands (subsets of the 32 cards)
// in Skat (a hand in skat always has 10 cards)

struct Leaf {
  std::vector<Leaf> children;
  unsigned int depth;
  Hand hand;
  Leaf(unsigned int depth, Hand hand) {
    this->depth = depth;
    this->hand = hand;
  }
  Leaf() {
    this->depth = 0;
    std::fill(begin(this->hand), end(this->hand), 0);
  }
};

class HandTree {
public:
  HandTree();
  ~HandTree();

  // Returns all allowed hands in respect to dealedHands.
  // dealedHands can be empty.
  void getAllHands(const Hand &sumHands, std::vector<Hand> &compatibleHands);

private:
  // creates the tree structure
  void populate(Leaf &leaf, Hand hand, unsigned int depth);

  // recursive helper function for getAllHands()
  void getAllHandsRec(const Leaf &leaf, const Hand &sumHands,
                      std::vector<Hand> &compatibleHands);

  Leaf mainLeaf;
};

#endif // HAND_TREE_H

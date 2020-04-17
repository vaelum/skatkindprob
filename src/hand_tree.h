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
// in Skat (a hand in Skat always has 10 cards)

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

// HandTree is a tree data structure using Leaf as nodes.
// HandTree contains all allowed hands for one player
// (subset of the 32 cards) in Skat (a hand in Skat
// always has 10 cards). Each level of the tree represents
// one of the 8 symbols and contains all the partially complete
// possible hands up to the current level.
// Every Leaf can have between 1 and 5 children depending on how many
// cards are already in the hand up to the current level.
class HandTree {
 public:
  HandTree();
  ~HandTree();

  // Returns all allowed hands in respect to dealedHands.
  // dealedHands can be empty.
  void getAllHands(const Hand &sumHands, std::vector<Hand> &compatibleHands);

 private:
  // populates/creates the tree structure
  void populate(Leaf &leaf, Hand hand, unsigned int depth);

  void getAllHandsRec(const Leaf &leaf, const Hand &sumHands,
                      std::vector<Hand> &compatibleHands);

  Leaf mainLeaf;
};

#endif  // HAND_TREE_H

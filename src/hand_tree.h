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
  std::vector<std::shared_ptr<Leaf>> children;
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

  // Returns all allowed hands in respect to dealedHands.
  // dealedHands can be empty.
  std::vector<Hand> getAllHands(std::vector<Hand> &dealedHands);

private:
  // creates the tree structure
  void populate(std::shared_ptr<Leaf> leaf, Hand hand, unsigned int depth);

  // recursive helper function for getAllHands()
  void getAllHandsRec(std::shared_ptr<Leaf> &leaf,
                      std::vector<Hand> &dealedHands,
                      std::vector<Hand> &retHands);

  std::shared_ptr<Leaf> mainLeaf;
};

#endif // HAND_TREE_H

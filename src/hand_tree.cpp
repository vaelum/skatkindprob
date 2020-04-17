#include "hand_tree.h"

HandTree::HandTree() {
  Hand hand;
  std::fill(begin(hand), end(hand), 0);
  this->populate(mainLeaf, hand, 0);
}

HandTree::~HandTree() {}

void HandTree::populate(Leaf &leaf, Hand hand, unsigned int depth) {
  for (unsigned int i = 0; i < 5; i++) {
    hand[depth] = i;

    // number of cards in hand including current level
    unsigned int handCards = std::accumulate(begin(hand), end(hand), 0);

    // ignore all hands with more than 10 cards (they are illegal in skat)
    if (handCards <= 10) {
      // stop recursive population
      if (depth + 1 == 8) {
        if (handCards == 10) {
          leaf.children.push_back(Leaf(depth + 1, hand));
        }
      }
      // continue recursive population
      else {
        leaf.children.push_back(Leaf(depth + 1, hand));
        this->populate(leaf.children.back(), hand, depth + 1);
      }
    }
  }
}

void HandTree::getAllHands(const Hand &sumHands,
                           std::vector<Hand> &compatibleHands) {
  for (const auto &leaf : mainLeaf.children) {
    this->getAllHandsRec(leaf, sumHands, compatibleHands);
  }
}

void HandTree::getAllHandsRec(const Leaf &leaf, const Hand &sumHands,
                              std::vector<Hand> &compatibleHands) {
  // checks if leaf->hand is still compatible with dealedHands by summing up
  // symbol count at leaf->depth - 1
  if (sumHands[leaf.depth - 1] + leaf.hand[leaf.depth - 1] <= 4) {
    // recursion stop
    if (leaf.depth == 8) {
      compatibleHands.push_back(leaf.hand);
      return;
    }

    for (const auto &c : leaf.children) {
      this->getAllHandsRec(c, sumHands, compatibleHands);
    }
  }
}

#include "hand_tree.h"

HandTree::HandTree() {
  Hand hand;
  std::fill(begin(hand), end(hand), 0);
  mainLeaf = std::make_shared<Leaf>(nullptr, 0, hand);

  this->populate(mainLeaf, hand, 0);
}

HandTree::~HandTree() {}

void HandTree::populate(std::shared_ptr<Leaf> leaf, Hand hand,
                        unsigned int depth) {
  for (unsigned int i = 0; i < 5; i++) {
    hand[depth] = i;
    unsigned int handCards = std::accumulate(begin(hand), end(hand), 0);
    if (handCards <= 10) {
      if (depth + 1 == 8) {
        if (handCards == 10) {
          leaf->children.push_back(
              std::make_shared<Leaf>(leaf, depth + 1, hand));
        }
      } else {
        leaf->children.push_back(std::make_shared<Leaf>(leaf, depth + 1, hand));
        this->populate(leaf->children.back(), hand, depth + 1);
      }
    }
  }
}

std::vector<Hand> HandTree::getAllHands(std::vector<Hand> &dealedHands) {
  std::vector<Hand> retHands;
  this->getAllHandsRec(mainLeaf->children[0], dealedHands, retHands);
  this->getAllHandsRec(mainLeaf->children[1], dealedHands, retHands);
  this->getAllHandsRec(mainLeaf->children[2], dealedHands, retHands);
  this->getAllHandsRec(mainLeaf->children[3], dealedHands, retHands);
  this->getAllHandsRec(mainLeaf->children[4], dealedHands, retHands);
  return retHands;
}

void HandTree::getAllHandsRec(std::shared_ptr<Leaf> &leaf,
                              std::vector<Hand> &dealedHands,
                              std::vector<Hand> &retHands) {
  // checks if leaf->hand is still compatible with dealedHands by summing up
  // symbol count at leaf->depth -1
  unsigned int symbolCount = 0;
  for (auto &dh : dealedHands) {
    symbolCount += dh[leaf->depth - 1];
  }
  symbolCount += leaf->hand[leaf->depth - 1];
  // actuall check
  if (symbolCount <= 4) {
    if (leaf->depth == 8) {
      retHands.push_back(leaf->hand);
      return;
    }
    for (auto &c : leaf->children) {
      this->getAllHandsRec(c, dealedHands, retHands);
    }
  }
}

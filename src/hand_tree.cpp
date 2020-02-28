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
    if (std::accumulate(begin(hand), end(hand), 0) <= 10) {
      if (depth + 1 == 8) {
        unsigned int sum = 0;
        for (auto v : hand) {
          sum += v;
        }
        if (sum == 10) {
          leaf->children[i] = std::make_shared<Leaf>(leaf, depth + 1, hand);
        }
      } else {
        leaf->children[i] = std::make_shared<Leaf>(leaf, depth + 1, hand);
        this->populate(leaf->children[i], hand, depth + 1);
      }
    } else {
      leaf->children[i] = nullptr;
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

  unsigned int sum = 0;
  for (unsigned int i = 0; i < dealedHands.size(); i++) {
    sum += dealedHands.at(i)[leaf->depth - 1];
  }
  sum += leaf->hand[leaf->depth - 1];

  if (sum <= 4) {
    if (leaf->depth == 8) {

      retHands.push_back(leaf->hand);
      return;
    }
    for (unsigned int i = 0; i < 5; i++) {
      if (leaf->children[i] != nullptr) {
        this->getAllHandsRec(leaf->children[i], dealedHands, retHands);
      }
    }
  }
}

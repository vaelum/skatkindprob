#include "hand_tree.h"

HandTree::HandTree() {
  Hand hand;
  mainLeaf = std::make_shared<Leaf>(nullptr, 0, hand);

  this->populate(mainLeaf, hand, 0);
}

HandTree::~HandTree() {}

void HandTree::populate(std::shared_ptr<Leaf> leaf, Hand hand,
                        unsigned int depth) {
  // remove after verifying no longer needed
  if (depth > 7) {
    std::cout << "SOMETHING WENT WRONG!!! No. 1" << std::endl;
    return;
  }

  for (unsigned int i = 0; i < 5; i++) {
    hand.symbol[depth] = i;
    if (this->isValidHand(hand)) {
      if (depth + 1 == 8) {
        unsigned int sum = 0;
        for (auto v : hand.symbol) {
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

bool HandTree::isValidHand(Hand &hand) {
  unsigned int sum = 0;
  for (auto v : hand.symbol) {
    sum += v;
  }
  return sum <= 10 ? true : false;
}

std::vector<Hand> HandTree::getAllHands(std::vector<Hand> &dealedHands) {
  std::vector<Hand> retHands;
  this->getAllHandsRec(mainLeaf, dealedHands, retHands);
  return retHands;
}

void HandTree::getAllHandsRec(std::shared_ptr<Leaf> &leaf,
                              std::vector<Hand> &dealedHands,
                              std::vector<Hand> &retHands) {
  if (this->areCompatibleHands(dealedHands, leaf->hand)) {
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

bool HandTree::areCompatibleHands(std::vector<Hand> &hands, Hand &h) {

  for (unsigned int i = 0; i < 8; i++) {
    unsigned int sum = 0;
    for (unsigned int k = 0; k < hands.size(); k++) {
      sum += hands.at(k).symbol[i];
    }
    sum += h.symbol[i];
    if (sum > 4) {
      return false;
    }
  }
  return true;
}
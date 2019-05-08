#include "node.h"
using namespace std;
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {
    assert(left == NULL && right == NULL);
    theMap.insert(make_pair(sym, b));
    return;
  }
  else {
    this->left->buildMap(b.plusZero(), theMap);
    this->right->buildMap(b.plusOne(), theMap);
  }
}

#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t tree;
  int array_size = 257;
  for (int i = 0; i < array_size; ++i) {
    if (counts[i] > 0) {
      tree.push(new Node(i, counts[i]));
    }
    else {
      continue;
    }
  }
  while (tree.size() > 1) {
    Node * temp1 = tree.top();
    tree.pop();
    Node * temp2 = tree.top();
    tree.pop();
    tree.push(new Node(temp1, temp2));
  }
  return tree.top();
}

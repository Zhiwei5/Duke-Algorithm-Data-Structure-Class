
#include <cassert>
#include <iostream>

#include "bstmap.h"

int main() {
  BstMap<int, int> a;
  a.remove(1);
  a.add(1, 1);
  a.add(9, 2);
  a.add(2, 3);
  a.add(8, 4);
  a.add(3, 5);
  a.add(7, 6);
  a.add(4, 7);
  a.add(6, 8);
  a.remove(1);
  a.remove(9);
  a.remove(4);
  int ans = a.lookup(3);
  std::cout << ans << std::endl;
  try {
    a.lookup(10000);
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }

  BstMap<int, char> * b = new BstMap<int, char>;
  b->add(4, 'a');
  b->add(1, 'b');
  char anserr = b->lookup(1);
  std::cout << "b expected:" << anserr << std::endl;
  b->add(1, 'c');
  anserr = b->lookup(1);
  std::cout << "c expected:" << anserr << std::endl;
  b->add(9, 'd');
  b->add(2, 'e');
  b->add(8, 'f');
  b->add(3, 'g');
  b->add(7, 'h');
  b->remove(4);
  b->remove(9);
  delete b;
  BstMap<int, int> c;
  c.add(5, 1);
  c.add(6, 1);
  c.add(7, 1);
  c.add(8, 1);
  c.add(9, 1);
  c.add(4, 1);
  c.add(3, 1);
  c.add(2, 1);
  c.add(1, 1);
  c.add(0, 1);
  BstMap<int, int> d;
  d = a;
  ans = d.lookup(3);
  c = a;
  ans = c.lookup(3);
  std::cout << ans << std::endl;
  return 0;
}

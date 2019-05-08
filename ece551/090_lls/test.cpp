#include <cassert>
#include <cstdlib>

#include "ll.h"
void testList(void) {
  LinkedList<int> a;
  assert(a.getSize() == 0);
  // assert(a.remove(5) == false);
  a.addFront(5);
  assert(a.getSize() == 1);
  assert(a.head == a.tail);
  assert(a.head->next == nullptr);
  assert(a.head->prev == nullptr);
  assert(a.head->data == 5);
  assert(a.head->data == a[0]);
  a.addBack(20);
  assert(a.head->next->data == 20);
  assert(a.head->prev == nullptr);
  assert(a.tail->data == 20);
  assert(a.tail->prev == a.head);
  assert(a.tail->next == nullptr);
  assert(a.head->next == a.tail);
  assert(a.getSize() == 2);
  LinkedList<int> b;
  b = a;
  assert(!b.remove(17));
  assert(a.head->data == b.head->data);
  assert(b.head->next->data == 20);
  assert(b.head->prev == nullptr);
  assert(b.tail->data == 20);
  assert(b.tail->prev == b.head);
  assert(b.tail->next == nullptr);
  assert(b.head->next == b.tail);
  assert(b.getSize() == 2);
  LinkedList<int> c(a);
  assert(c.head->next->data == 20);
  assert(c.head->prev == nullptr);
  assert(c.tail->data == 20);
  assert(c.tail->prev == c.head);
  assert(c.tail->next == nullptr);
  assert(c.head->next == c.tail);
  assert(c.getSize() == 2);
  a.addBack(10);
  assert(a.head->next->next == a.tail);
  assert(a.tail->prev->data == 20);
  assert(a.tail->data == 10);
  a.remove(5);
  assert(a.getSize() == 2);
  assert(a.head->data == 20);
  assert(a.tail->data == 10);
  a.remove(10);
  assert(a.head->data == 20);
  assert(a.tail->data == 20);
  assert(a.getSize() == 1);
  assert(a.head == a.tail);
  assert(a.head->next == nullptr);
  assert(a.head->prev == nullptr);
  assert(a.head->data == 20);
  LinkedList<int> d;
  d.addFront(5);
  d.addBack(10);
  d.addBack(15);
  d.addBack(20);
  d.addBack(15);
  d.remove(22);
  assert(d[4] == 15);
  d.remove(15);
  assert(d.size == 4);
  assert(d.head->next->next->next == d.tail);
  assert(d.head->data == 5);
  assert(d.tail->data == 15);
  assert(d[2] == 20);
  assert(d.find(15) == 3);
  assert(d.find(0) == -1);
  assert(d.head->prev == nullptr);
  assert(d.tail->next == nullptr);
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}

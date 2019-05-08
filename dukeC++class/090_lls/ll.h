#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <exception>

class IndexOverFlowException
{};
//YOUR CODE GOES HERE
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * current = rhs.head;
    while (current != NULL) {
      this->addBack(current->data);
      current = current->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList temp(rhs);
    std::swap(head, temp.head);
    std::swap(tail, temp.tail);
    std::swap(size, temp.size);
    //destruct temp;
    while (temp.head != NULL) {
      Node * temp_node = temp.head;
      temp.head = temp.head->next;
      delete temp_node;
    }
    temp.tail = NULL;
    return *this;
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head;
      head = head->next;
      delete temp;
    }
    tail = NULL;
  }
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  bool remove(const T & item) {
    if (size == 0) {
      return false;
    }
    Node ** curr = &head;
    while ((*curr) != NULL) {
      if ((*curr)->data == item) {
        if ((*curr)->next == NULL) {
          Node * temp = *curr;
          tail = (*curr)->prev;
          *curr = (*curr)->next;
          delete temp;
        }
        else {
          Node * temp = *curr;
          (*curr)->next->prev = (*curr)->prev;
          *curr = (*curr)->next;
          delete temp;
        }
        size--;
        return true;
      }
      curr = &((*curr)->next);
    }
    return false;
  }
  T & operator[](int index) {
    if (index > size - 1) {
      throw IndexOverFlowException();
    }
    Node * current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }
  const T & operator[](int index) const {
    if (index > size - 1) {
      throw IndexOverFlowException();
    }
    Node * current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }
  int find(const T & item) {
    Node * current = head;
    int i = 0;
    while (current != NULL) {
      if (current->data == item) {
        return i;
      }
      current = current->next;
      ++i;
    }
    return -1;
  }
  int getSize() const { return size; }
  friend void testList(void);
};

#endif

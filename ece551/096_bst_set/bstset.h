/* -*- C++ -*- */

#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <stdexcept>

#include "set.h"

template<typename T>
class BstSet : public Set<T>
{
 private:
  class node
  {
   public:
    T Key;
    node * left;
    node * right;
    node(T inkey) : Key(inkey), left(NULL), right(NULL) {}
  };

 public:
  node * root;
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) : root(NULL) { buildtree(root, rhs.root); }
  BstSet & operator=(const BstSet & rhs) {
    BstSet temp(rhs);
    std::swap(root, temp.root);
    return *this;
  }

  void buildtree(node *& curr, node * rhs) {
    if (rhs != NULL) {
      curr = new node(rhs->Key);
      buildtree(curr->left, rhs->left);
      buildtree(curr->right, rhs->right);
    }
  }

  virtual void add(const T & key) {
    node ** curr = &root;
    while ((*curr) != NULL) {
      if ((*curr)->Key == key) {
        return;
      }
      else if ((*curr)->Key > key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
    *curr = new node(key);
  }
  virtual bool contains(const T & key) const {
    node * current = root;
    while (current != NULL) {
      if (current->Key == key) {
        return true;
      }
      else if (key < current->Key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }

  virtual void remove(const T & key) {
    node ** curr = &root;
    while ((*curr) != NULL) {
      if ((*curr)->Key == key) {
        if ((*curr)->left == NULL) {
          node * temp = (*curr);
          (*curr) = (*curr)->right;
          delete temp;
          return;
        }
        else if ((*curr)->right == NULL) {
          node * temp = (*curr);
          (*curr) = (*curr)->left;
          delete temp;
          return;
        }
        else {
          node ** curr_r = &((*curr)->right);
          while ((*curr_r)->left != NULL) {
            curr_r = &((*curr_r)->left);
          }
          node * temp = (*curr_r);
          (*curr_r) = (*curr_r)->right;
          (*curr)->Key = temp->Key;
          delete temp;
          return;
        }
      }
      else if (key < (*curr)->Key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
  }
  void delete_tree(node * current) {
    if (current != NULL) {
      delete_tree(current->left);
      delete_tree(current->right);
      delete current;
    }
  }

  virtual ~BstSet<T>() { delete_tree(root); }
};
#endif

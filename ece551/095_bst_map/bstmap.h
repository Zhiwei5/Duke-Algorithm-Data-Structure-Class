/* -*- C++ -*- */

#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <algorithm>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  class node
  {
   public:
    K Key;
    V Value;
    node * left;
    node * right;
    node(K inkey, V invalue) : Key(inkey), Value(invalue), left(NULL), right(NULL) {}
  };

 public:
  node * root;
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) { buildtree(root, rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    BstMap temp(rhs);
    std::swap(root, temp.root);
    // delete_tree(temp.root);  if i delete here then that would be invalid double free
    return *this;
  }

  void buildtree(node *& curr, node * rhs) {
    if (rhs != NULL) {
      curr = new node(rhs->Key, rhs->Value);
      buildtree(curr->left, rhs->left);
      buildtree(curr->right, rhs->right);
    }
  }

  // public:
  virtual void add(const K & key, const V & value) {
    node ** curr = &root;
    while ((*curr) != NULL) {
      if ((*curr)->Key == key) {
        (*curr)->Value = value;
        return;
      }
      else if ((*curr)->Key > key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
    *curr = new node(key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    node * current = root;
    while (current != NULL) {
      if (current->Key == key) {
        return current->Value;
      }
      else if (key < current->Key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    // delete_tree(root);
    throw std::invalid_argument("did not find the key");
  }

  virtual void remove(const K & key) {
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
          (*curr)->Value = temp->Value;
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

  virtual ~BstMap<K, V>() { delete_tree(root); }
};

#endif

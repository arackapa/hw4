#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* conversion(Node<Key, Value>* n) const; 
    void rightRotate(AVLNode<Key,Value>* n);
    void leftRotate(AVLNode<Key,Value>* n);
    void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void removeFix(AVLNode<Key, Value>* n, int8_t diff);  
};


template<class Key, class Value>
AVLNode<Key, Value> *AVLTree<Key, Value>::conversion(Node<Key, Value>* n) const
{
    return static_cast<AVLNode<Key, Value>*>(n);
}



/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // base case if tree is empty, set n as root, b(n) = 0 
    if (this->root_ == NULL)
    {
      // std::cout << "empty tree and setting the root" << std::endl; 
      AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL); 
      this->root_ = newNode; 
    }
    else
    {
      // if there is something in the tree, we need to compare the keys
      // if less than go left, if greater than go right  
      AVLNode<Key, Value>* traveler = conversion(this->root_);
      
      while (traveler != NULL) 
      {
        // go left since key is less than 
        if (traveler->getKey() > new_item.first) 
        {
          // if there is nothing left, we create the node here and end the loop 
          if (traveler->getLeft() == NULL)
          {
            AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, traveler);
            traveler->setLeft(newNode);
            // adding a left node, we must increase the balance of parent by -1 
            if (traveler->getBalance() == -1) traveler->setBalance(0); 
            else if (traveler->getBalance() == 1) traveler->setBalance(0);  
            else if (traveler->getBalance() == 0) 
            {
              traveler->setBalance(-1); 
              insertFix(traveler, newNode);
            }
            break; 
          }
          traveler = traveler->getLeft(); 
        }
        // if key is the same, set the value 
        else if (traveler->getKey() == new_item.first)
        {
          traveler->setValue(new_item.second);
          break; 
        }
        //otherwise if the key is greater than, go right 
        else if (traveler->getKey() < new_item.first)
        {
          if (traveler->getRight() == NULL)
          {
            AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, traveler); 
            traveler->setRight(newNode); 
            // adding a right node, we must increase balance of parent by 1 
            if (traveler->getBalance() == -1) traveler->setBalance(0); 
            else if (traveler->getBalance() == 1) traveler->setBalance(0);  
            else if (traveler->getBalance() == 0) 
            {
              traveler->setBalance(1); 
              insertFix(traveler, newNode);
            }
            break;
          }
          traveler = traveler->getRight(); 
        }
      }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n)
{
  AVLNode<Key, Value>* g = p->getParent(); 

  if (p == NULL || g == NULL) return; 
  else if (g->getLeft() == p)
  {
    g->updateBalance(-1);
    if (g->getBalance() == 0) return; 
    else if (g->getBalance() == -1) insertFix(g, p);
    else if (g->getBalance() == -2) 
    {
      // left left case 
      if (p->getLeft() == n) 
      {
        p->setBalance(0);
        g->setBalance(0); 
        rightRotate(g); 
      }
      // left right case 
      else if (p->getRight() == n)
      {
        leftRotate(p);
        rightRotate(g);
        if (n->getBalance() == -1)
        {
          p->setBalance(0);
          g->setBalance(1); 
          n->setBalance(0);
        }
        else if (n->getBalance() == 0)
        {
          p->setBalance(0); 
          g->setBalance(0);
          n->setBalance(0);
        }
        else if (n->getBalance() == 1)
        {
          p->setBalance(-1); 
          g->setBalance(0);
          n->setBalance(0);
        }
      }
    }

  }
  else if (g->getRight() == p)
  {
    g->updateBalance(1);
    if (g->getBalance() == 0) return; 
    else if (g->getBalance() == 1) insertFix(g, p);
    else if (g->getBalance() == 2) 
    {
    // right right case 
      if (p->getRight() == n) 
      {
        leftRotate(g);
        p->setBalance(0);
        g->setBalance(0); 
      }
      // left right case 
      else if (p->getLeft() == n)
      {
        rightRotate(p);
        leftRotate(g);
        if (n->getBalance() == 1)
        {
          p->setBalance(0);
          g->setBalance(-1); 
          n->setBalance(0);
        }
        else if (n->getBalance() == 0)
        {
          p->setBalance(0); 
          g->setBalance(0);
          n->setBalance(0);
        }
        else if (n->getBalance() == -1)
        {
          p->setBalance(1); 
          g->setBalance(0);
          n->setBalance(0);
        }
      }
    }
  }

}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
     // find the value by walking the tree 
    AVLNode<Key, Value>* removal = conversion(this->internalFind(key)); 
    int8_t diff = 0;
    // if the value is not found we stop 
    if (removal == NULL) return; 
    // 0 child case --> left and right children are NULL
    else if (removal->getRight() == NULL && removal->getLeft() == NULL)
    {
      if (removal == this->root_) 
      {
        this->root_ = NULL; 
      }
    }
    // 2 child case --> left and right child are not NULL 
    else if (removal->getRight() != NULL && removal->getLeft() != NULL)
    {
      AVLNode<Key, Value>* temp = removal; 
      temp = conversion(this->predecessor(removal)); 
      // check if a predecessor exists
      if (temp == NULL){}
      else
      {
        nodeSwap(removal, temp); 
        // if the root was what just got swapped, update it 
        if (removal == this->root_)
        {
          this->root_ = temp; 
        }
          // do 0 child case with the swapped node 
        if (removal->getRight() == NULL && removal->getLeft() == NULL)
        {
          // root is swapped out so we don't have to consider that case 
          temp = removal->getParent(); 
        }
        // or do 1 child case with the swapped node 
        else if (removal->getRight() != NULL || removal->getLeft() != NULL)
        {
          // if node has a right child 
          if (removal->getRight() != NULL) 
          {
            if (removal == this->root_) 
            {
              this->root_ = removal->getRight(); 
              this->root_ = NULL; 
            }
            // see whether the node is a left or right node 
            else if (removal->getParent()->getRight() == removal)
            {
              // set the current node location to the right child 
              AVLNode<Key, Value>* parent = removal->getParent(); 
              parent->setRight(removal->getRight()); 
              parent->getRight()->setParent(parent); 
            }
            else if (removal->getParent()->getLeft() == removal)
            {
              // set the current node location to the left child 
              AVLNode<Key, Value>* parent = removal->getParent(); 
              parent->setLeft(removal->getRight()); 
              parent->getLeft()->setParent(parent); 
            }
            // delete removal; 
          }
          // if root has a left child  
          else if (removal->getLeft() != NULL) 
          {
            // if the spot of removal is root we must update root value 
            if (removal == this->root_) 
            {
              this->root_ = removal->getLeft(); 
            }
            // otherwise we check whether this is a left or right node and adjust the parent 
            else if (removal->getParent()->getRight() == removal)
            {
              AVLNode<Key, Value>* parent = removal->getParent(); 
              parent->setRight(removal->getLeft()); 
              parent->getRight()->setParent(parent); 
            }
            else if (removal->getParent()->getLeft() == removal)
            {
              AVLNode<Key, Value>* parent = removal->getParent(); 
              parent->setLeft(removal->getLeft()); 
              parent->getLeft()->setParent(parent); 
            }
          }
        }
      }
    }
    // 1 child case --> either the left or right child is NULL 
    else if (removal->getRight() != NULL || removal->getLeft() != NULL)
    {
        // if node has a right child 
        if (removal->getRight() != NULL) 
        {
          if (removal == this->root_) 
          {
            this->root_ = removal->getRight(); 
            this->root_->setParent(NULL); 
          }
          // see whether the node is a left or right node 
          else if (removal->getParent()->getRight() == removal)
          {
            // set the current node location to the right child 
            AVLNode<Key, Value>* parent = removal->getParent(); 
            parent->setRight(removal->getRight()); 
            parent->getRight()->setParent(parent); 
          }
          else if (removal->getParent()->getLeft() == removal)
          {
            // set the current node location to the left child 
            AVLNode<Key, Value>* parent = removal->getParent(); 
            parent->setLeft(removal->getRight()); 
            parent->getLeft()->setParent(parent); 
          }
        }
        // if root has a left child  
        else if (removal->getLeft() != NULL) 
        {
          // if the spot of removal is root we must update root value 
          if (removal == this->root_) 
          {
            this->root_ = removal->getLeft(); 
            this->root_->setParent(NULL); 
          }
          // otherwise we check whether this is a left or right node and adjust the parent 
          else if (removal->getParent()->getRight() == removal)
          {
            AVLNode<Key, Value>* parent = removal->getParent(); 
            parent->setRight(removal->getLeft()); 
            parent->getRight()->setParent(parent); 
          }
          else if (removal->getParent()->getLeft() == removal)
          {
            AVLNode<Key, Value>* parent = removal->getParent(); 
            parent->setLeft(removal->getLeft()); 
            parent->getLeft()->setParent(parent); 
          }
        }
      }

      AVLNode<Key, Value>* p = removal->getParent(); 

    if (p != NULL)
    {
        if (p->getLeft() == removal)
        {
            diff = 1;
            p->setLeft(NULL);
        }
        if (p->getRight() == removal)
        {
            diff = -1; 
            p->setRight(NULL); 
        }
    }
    
    delete removal; 
    removeFix(p, diff); 
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int8_t diff)
{
  if (n == NULL) return; 

  int8_t ndiff = 0; 
  AVLNode<Key, Value>* p = n->getParent(); 
  // computing next recursive call's arguments before altering tree 
  if (p != NULL && p->getLeft() == n)
  {
    ndiff = 1; 
  }
  else // if (p!= NULL && p->getRight() == n)
  {
    ndiff = -1;
  }

  if (diff == -1)
  {
    if ((n->getBalance() + diff) == -2)
    {
      AVLNode<Key, Value>* c = n->getLeft(); 
      // zig zig case 
      if (c->getBalance() == -1)
      {
        rightRotate(n); 
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      else if (c->getBalance() == 0)
      {
        rightRotate(n); 
        n->setBalance(-1);
        c->setBalance(1);
      }
      else if (c->getBalance() == 1)
      {
        AVLNode<Key, Value>* g = c->getRight(); 
        leftRotate(c);
        rightRotate(n);
        if (g->getBalance() == 1)
        {
          n->setBalance(0);
          c->setBalance(-1);
          g->setBalance(0);
        }
        else if (g->getBalance() == 0)
        {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if (g->getBalance() == -1)
        {
          n->setBalance(1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    else if ((n->getBalance() + diff) == -1)
    {
      n->setBalance(-1);
    }
    else if ((n->getBalance() + diff) == 0)
    {
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
  // this is the mirror case 
  else if (diff == 1)
  {
    if ((n->getBalance() + diff) == 2)
    {
      AVLNode<Key, Value>* c = n->getRight(); 
      // zig zig case 
      if (c->getBalance() == 1)
      {
        leftRotate(n); 
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      else if (c->getBalance() == 0)
      {
        leftRotate(n); 
        n->setBalance(1);
        c->setBalance(-1);
      }
      // zig zag case 
      else if (c->getBalance() == -1)
      {
        AVLNode<Key, Value>* g = c->getLeft(); 
        rightRotate(c);
        leftRotate(n);
        if (g->getBalance() == -1)
        {
          n->setBalance(0);
          c->setBalance(1);
          g->setBalance(0);
        }
        else if (g->getBalance() == 0)
        {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if (g->getBalance() == 1)
        {
          n->setBalance(-1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    else if ((n->getBalance() + diff) == 1)
    {
      n->setBalance(1);
    }
    else if ((n->getBalance() + diff) == 0)
    {
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
}


template<class Key, class Value>
void AVLTree<Key, Value>:: leftRotate(AVLNode<Key,Value>* n)
{
  AVLNode<Key,Value>* rightNode = n->getRight(); 
  AVLNode<Key,Value>* p = n->getParent(); 
  if (n == NULL) return; 
  if (rightNode == NULL) return; 
  
  if (n == this->root_)
  {
    this->root_ = rightNode; 
  }
  else if (p->getLeft() == n)
  {
    p->setLeft(rightNode); 
  }
  else if (p->getRight() == n)
  {
    p->setRight(rightNode); 
  }
  n->setParent(rightNode); 
  n->setRight(rightNode->getLeft()); 
  if (rightNode->getLeft() != NULL)
  {
    rightNode->getLeft()->setParent(n); 
  }
  rightNode->setLeft(n);
  rightNode->setParent(p);
}



template<class Key, class Value>
void AVLTree<Key, Value>:: rightRotate(AVLNode<Key,Value>* n)
{
  AVLNode<Key,Value>* leftNode = n->getLeft(); 
  AVLNode<Key,Value>* p = n->getParent(); 

  // if we are rotating at the root level, we want to update the root of the tree 
  if (n == NULL) return; 
 
  // if n is the root that means there is no parent 

  if (n == this->root_)
  {
    this->root_ = leftNode; 
  }
  else if (p->getLeft() == n)
  {
    p->setLeft(leftNode); 
  }
  else if (p->getRight() == n)
  {
    p->setRight(leftNode); 
  }

  // shifting node n to the right and updating its parent to the left node 
  n->setParent(leftNode); 

  // shifting over the left right subtree to the right tree 
  n->setLeft(leftNode->getRight()); 

  if (leftNode->getRight() != NULL)
  {
    leftNode->getRight()->setParent(n); 
  }

  // updating left node as the central node 
  leftNode->setRight(n);
  leftNode->setParent(p); 

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif

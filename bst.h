#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    int calculateHeightIfBalanced(Node<Key, Value>* root) const;
    static void successor(Node<Key, Value>*& current); 
    int leafDelete(Node<Key, Value>* const root);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr; 
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
  current_ = NULL; 
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (this->current_ == NULL && rhs.current_ == NULL) return true; 
    else if (this->current_ == NULL || rhs.current_ == NULL) return false; 
    if (this->current_->getKey() == rhs.current_->getKey() && this->current_->getValue() == rhs.current_->getValue()) return true;
    else return false; 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool  
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (*this == rhs) return false;
    else return true; 
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    successor(current_); 
    return *this; 
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL; 
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear(); 
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    // if there is nothing in the tree this node becomes the root 
    if (root_ == NULL)
    {
      Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
      root_ = newNode; 
    }
    else
    {
      // if there is something in the tree, we need to compare the keys
      // if less than go left, if greater than go right  
      Node<Key, Value>* traveler = root_;
      
      while (traveler != NULL) 
      {
        // go left since key is less than 
        if (traveler->getKey() > keyValuePair.first) 
        {
          // if there is nothing left, we create the node here and end the loop 
          if (traveler->getLeft() == NULL)
          {
            Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, traveler); 
            traveler->setLeft(newNode); 
            break; 
          }
          traveler = traveler->getLeft(); 
        }
        // if key is the same, set the value 
        else if (traveler->getKey() == keyValuePair.first)
        {
          traveler->setValue(keyValuePair.second);
          break; 
        }
        //otherwise if the key is greater than, go right 
        else if (traveler->getKey() < keyValuePair.first)
        {
          if (traveler->getRight() == NULL)
          {
            Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, traveler); 
            traveler->setRight(newNode); 
            break;
          }
          traveler = traveler->getRight(); 
        }
      }
    } 
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // find the value by walking the tree 
    Node<Key, Value>* removal = internalFind(key); 
    
    // if the value is not found we stop 
    if (removal == NULL) return; 
    // 0 child case --> left and right children are NULL
    else if (removal->getRight() == NULL && removal->getLeft() == NULL)
    {
      if (removal == root_) 
      {
        delete removal; 
        root_ = NULL; 
      }
      else 
      {
        Node<Key, Value>* temp = removal; 
        temp = removal->getParent(); 
        // if left child vs right child, set the parent accordingly 
        if (removal == temp->getLeft()) temp->setLeft(NULL); 
        else if (removal == temp->getRight()) temp->setRight(NULL); 
        // then delete the node 
        delete removal; 
      }
    }
    // 2 child case --> left and right child are not NULL 
    else if (removal->getRight() != NULL && removal->getLeft() != NULL)
    {
      Node<Key, Value>* temp = removal; 
      temp = predecessor(removal); 
      // check if a predecessor exists
      if (temp == NULL)
      {

      }
      else
      {
        nodeSwap(removal, temp); 
        // if the root was what just got swapped, update it 
        if (removal == root_)
        {
          root_ = temp; 
        }
          // do 0 child case with the swapped node 
        if (removal->getRight() == NULL && removal->getLeft() == NULL)
        {
          // root is swapped out so we don't have to consider that case 
          Node<Key, Value>* temp = removal; 
          temp = removal->getParent(); 
          // if left child vs right child, set the parent accordingly 
          if (removal == temp->getLeft()) temp->setLeft(NULL); 
          else if (removal == temp->getRight()) temp->setRight(NULL); 
          // then delete the node 
          delete removal; 
        }
        // or do 1 child case with the swapped node 
        else if (removal->getRight() != NULL || removal->getLeft() != NULL)
        {
          // if node has a right child 
          if (removal->getRight() != NULL) 
          {
            if (removal == root_) 
            {
              root_ = removal->getRight(); 
              root_ = NULL; 
            }
            // see whether the node is a left or right node 
            else if (removal->getParent()->getRight() == removal)
            {
              // set the current node location to the right child 
              Node<Key, Value>* parent = removal->getParent(); 
              parent->setRight(removal->getRight()); 
              parent->getRight()->setParent(parent); 
            }
            else if (removal->getParent()->getLeft() == removal)
            {
              // set the current node location to the left child 
              Node<Key, Value>* parent = removal->getParent(); 
              parent->setLeft(removal->getRight()); 
              parent->getLeft()->setParent(parent); 
            }
            delete removal; 
          }
          // if root has a left child  
          else if (removal->getLeft() != NULL) 
          {
            // if the spot of removal is root we must update root value 
            if (removal == root_) 
            {
              root_ = removal->getLeft(); 
            }
            // otherwise we check whether this is a left or right node and adjust the parent 
            else if (removal->getParent()->getRight() == removal)
            {
              Node<Key, Value>* parent = removal->getParent(); 
              parent->setRight(removal->getLeft()); 
              parent->getRight()->setParent(parent); 
            }
            else if (removal->getParent()->getLeft() == removal)
            {
              Node<Key, Value>* parent = removal->getParent(); 
              parent->setLeft(removal->getLeft()); 
              parent->getLeft()->setParent(parent); 
            }
            delete removal; 
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
          if (removal == root_) 
          {
            root_ = removal->getRight(); 
            root_->setParent(NULL); 
          }
          // see whether the node is a left or right node 
          else if (removal->getParent()->getRight() == removal)
          {
            // set the current node location to the right child 
            Node<Key, Value>* parent = removal->getParent(); 
            parent->setRight(removal->getRight()); 
            parent->getRight()->setParent(parent); 
          }
          else if (removal->getParent()->getLeft() == removal)
          {
            // set the current node location to the left child 
            Node<Key, Value>* parent = removal->getParent(); 
            parent->setLeft(removal->getRight()); 
            parent->getLeft()->setParent(parent); 
          }
          delete removal; 
        }
        // if root has a left child  
        else if (removal->getLeft() != NULL) 
        {
          // if the spot of removal is root we must update root value 
          if (removal == root_) 
          {
            root_ = removal->getLeft(); 
            root_->setParent(NULL); 
          }
          // otherwise we check whether this is a left or right node and adjust the parent 
          else if (removal->getParent()->getRight() == removal)
          {
            Node<Key, Value>* parent = removal->getParent(); 
            parent->setRight(removal->getLeft()); 
            parent->getRight()->setParent(parent); 
          }
          else if (removal->getParent()->getLeft() == removal)
          {
            Node<Key, Value>* parent = removal->getParent(); 
            parent->setLeft(removal->getLeft()); 
            parent->getLeft()->setParent(parent); 
          }
          delete removal; 
        }
      }
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // steps to get predecessor 
    // check if left child exists 
    if (current->getLeft() != NULL) 
    {
      current = current->getLeft(); 
      // if it does we must walk down to the right most node 
      while (current->getRight() != NULL) 
      {
        current = current->getRight(); 
      }
      return current; 
    }
    // if no left child exists 
    else 
    {
      while (current->getParent() != NULL)
      {
        current = current->getParent(); 
        if (current->getRight() != NULL) return current; 
      }
      return NULL; 
    }
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::successor(Node<Key, Value>*& current)
{
    // TODO
    // steps to get predecessor 
    Node<Key, Value>* temp = current; 
    if (temp->getRight() != NULL)
    {
      temp = temp->getRight(); 
      // if it does we must walk down to the left most node 
      while (temp->getLeft() != NULL) 
      {
        temp = temp->getLeft(); 
      }
      current = temp; 
      return; 
    }
    else
    {
      // no parent means we are at the root, so no successor
      // the error is somewhere here 
      if (temp->getParent() == NULL)
      {
        if (temp->getLeft() == NULL && temp->getRight() == NULL)
        {
          current = NULL; 
        }
        else 
        {
          current = temp; 
        }
        return; 
      }
      // if there is a parent, is there a grandparent? 
      else 
      {
        // there is no grandparent, so we check if temp is a left or right child 
        if (temp->getParent()->getParent() == NULL)
        {
          if (temp->getParent()->getLeft() == temp)
          {
            current = temp->getParent(); 
            return; 
          }
          else if (temp->getParent()->getRight() == temp)
          {
            current = NULL;
            return; 
          }
        }
        // a grandparent exists so now we can look for a parent that is a left child of grandparent 
        else
        {
          Node<Key, Value>* grandParent = temp->getParent()->getParent(); 
          Node<Key, Value>* parent = temp->getParent(); 
          // if no right child and temp is a left node, we climb the tree looking for first left node 
            while (grandParent != NULL)
            {
              if (grandParent->getLeft() == parent)
              {
                current = grandParent; 
                return; 
              }
              parent = parent->getParent();
              grandParent = grandParent->getParent(); 
            }
            // no successor if we climb the tree and do not find anyone who is a left child. 
            current = NULL; 
        }
      }
    }
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    leafDelete(root_); 
    root_ = NULL; 
}

/* Helper function to recursively reach leaf nodes and delete them */ 
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::leafDelete(Node<Key, Value>* root)
{
    // TODO
    // if we go past a leaf node we need to stop 
    if (root == nullptr) return 0; 
    
    // doing the recursion in an if statement so that we stop the recursion and return a -1 if at anypoint the leaf is different than depth 
    leafDelete(root->getLeft());
    leafDelete(root->getRight());
    
    // only act on the nodes once we have reached a leaf 
    if (root->getLeft() == NULL and root->getRight() == NULL)
    {
      Node<Key, Value>* temp = root; 
      temp = root->getParent(); 
      // look at parent, if parent is NULL, return 0; 
      if (temp == NULL) {}
      // if there is a parent, we need to check which child is the one we are trying to delete 
      else if (temp->getRight() == root) temp->setRight(NULL); 
      else if (temp->getLeft() == root) temp->setLeft(NULL); 
      
      delete root; 
    }
    return 0;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* temp = root_; 
    if(root_ == NULL) return NULL; 
    else if (root_->getLeft() == NULL) return root_; 
    else if(root_->getLeft() != NULL)
    {
      while(temp->getLeft() != NULL)
      {
        temp = temp->getLeft(); 
      }
    }
    return temp; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* traveler = root_; 
    if (traveler == NULL) return NULL; 
    while (traveler != NULL)
    {
      // if we find the key, return the node 
      if (traveler->getKey() == key)
      {
        return traveler; 
      }
      // if the key is less than the node key, then go left 
      else if (traveler->getKey() > key)
      {
        traveler = traveler->getLeft(); 
      }
      // if the key is greater than the node key, then go right 
      else
      {
        traveler = traveler->getRight(); 
      }
    }
    // if we go through the tree and don't find the key return NULL
    return NULL; 
}


/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    int result = calculateHeightIfBalanced(root_);
    if (result == -1) return false;
    else return true; 
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateHeightIfBalanced(Node<Key, Value>* root) const 
{
	// Base case: an empty tree is always balanced and has a height of 0
	if (root == nullptr) return 0;
	
	int leftheight = calculateHeightIfBalanced(root->getLeft()); 
	int rightheight = calculateHeightIfBalanced(root->getRight()); 
	// Think about cases to handle:
	// - What if at least one subtree is NOT balanced?
	// - What if BOTH are balanced?
	int difference;
	if (leftheight > rightheight) difference = leftheight - rightheight; 
	else difference = rightheight - leftheight;  
	
	// TODO: handle the cases here
	if (leftheight == -1 or rightheight == -1)
	{
		return -1; 
	}
	else if (difference > 1)
	{
		return -1; 
	}
	else
	{
		if (leftheight > rightheight) return 1 + leftheight; 
		else return 1 + rightheight; 
	}
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif

#include "equal-paths.h"
#include <iostream>
using namespace std;


// You may add any prototypes of helper functions here
int equalPathsHelper(Node* root, int depth, int& leaf); 

bool equalPaths(Node * root)
{
    int leaf = 0;
    int depth = equalPathsHelper(root, 0, leaf); 
    if (depth == -1) return false;
    else return true; 
}

// helper function that uses post order traversal 
// incrementing depth at the start 
// doing recursion at the very end 
// this function returns a -1 if not equal node length to the root, and depth (non -1 number) if it is equal length to the root 
int equalPathsHelper(Node* root, int depth, int& leaf){
  // if we go past a leaf node we need to stop 
  if (root == nullptr) return 0; 
  depth++; 
  // only act on the nodes once we have reached a leaf 
  if (root->left == NULL and root->right == NULL)
  {
    // if the leaf == 0 --> this is our first leaf and we need to make it equal to the depth 
    if (leaf == 0)
    {
      leaf = depth; 
    }
    // if the leaf is not equal to the depth we return -1 --> this is then caught by the if statement below 
    if (leaf != depth) return -1; 
  }
  // doing the recursion in an if statement so that we stop the recursion and return a -1 if at anypoint the leaf is different than depth 
  if (equalPathsHelper(root->left, depth, leaf) == -1) return -1;
  if (equalPathsHelper(root->right, depth,leaf) == -1) return -1;
  else return depth; 
}; 

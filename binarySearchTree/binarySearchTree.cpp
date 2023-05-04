#include <iostream>
#include <iomanip>
#include "binarySearchTree.h"

#define underline "\033[4m"
#define unreset "\033[24m"
using namespace std;

binarySearchTree::binarySearchTree(){
  tree->root = nullptr;
  this->size = 0;
}

binarySearchTree::~binarySearchTree(){
  this->destructor(this->root);
}

void binarySearchTree::destructor(Node *current){
  if(current == nullptr)
    return;

  Node *left = current->left;
  Node *right = current->right;
  delete current;

  destructor(left);
  destructor(right);
}

void binarySearchTree::add(int add){
  if(this->root == nullptr){
    this->root = new Node(data);
    return;
  }
  this->add(this->root, data);
}

Node *binarySearchTree::add(Node *current, int data){
  if(current == nullptr)
    return new Node(data);
  if(data > current->data)
    current->right = add(current->right, data);
  else if(data < current->data)
    current->left = add(current->left, data);
  return current;
}

void binarySearchTree::remove(int data){
  this->root = this->remove(this->root, data);
}

Node *binarySearchTree::remove(Node *current, int value){
  if(current == nullptr)
    return current;
  if(value < current->data)
    current->left = this->remove(current->left, value);
  else if(value > current->data)
    current->right = this->remove(current->right, value);
  else{
    if(current->left == nullptr && current->right == nullptr){
      delete current;
      current = nullptr;
    }
    else if(current->left == nullptr){
      Node *temp = current;
      current = current->right;
      delete temp;
    }
    else if(current->right == nullptr){
      Node *temp = current;
      current = current->left;
      delete temp;
    }
    else{
      Node *temp = this->minValueNode(current->right);
      current->data = temp->data;
      current->right = this->remove(current->right, temp->data);
    }
  }
  return current;
}

bool binarySearchTree::search(int data){
  return this->search(this->root, data);
}

bool binarySearchTree::search(Node *current, int data){
  if(current == nullptr)
    return false;
  if(current->data == data)
    return true;
  if(data < current->data)
    return search(current->left, data);
  else
    return search(current->right, data);
}

void binarySearchTree::display(){
  this->display(this->root, false, 0);
}

void binarySearchTree::display(Node* current, bool left, int depth){
  if(current == nullptr)
    return;
  display(current->right, false, depth+1);
  cout << setw(depth*5);
  if(left)
    cout << "\\";
  else{
    if(current != this->root)
      cout << "/";
  }
  cout << underline << current->data << reset << endl;
  display(current->left, true, depth+1);
}

Node *binarySearchTree::minValueNode(Node *node){
  Node *current = node;
  while (current && current->left != nullptr){
    current = current->left;
  }
  return current;
}

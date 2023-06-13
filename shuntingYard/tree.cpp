#include <iostream>
#include "tree.h"

using namespace std;

expressionTree::expressionTree() {
    root = nullptr;
}

expressionTree::~expressionTree() {
    delete root;
}

bool expressionTree::empty() {
    return (root == nullptr);
}

void expressionTree::setRoot(treeNode<char> *newRoot) {
    this->root = newRoot;
}

void expressionTree::traverseInfix(treeNode<char> *node)
{
    if (node != nullptr) {
        if (!node->isOperator())
            cout << node->data << " ";
        else {
            cout << "( ";
            traverseInfix(node->right);
            cout << node->data << " ";
            traverseInfix(node->left);
            cout << ") ";
        }
    }
}

void expressionTree::traversePrefix(treeNode<char> *node) {
    if (node != nullptr)
    {
        if (!node->isOperator())
        {
            cout << node->data << " ";
        }
        else
        {
            cout << node->data << " ";
            traversePrefix(node->right);
            traversePrefix(node->left);
        }
    }
}

void expressionTree::traversePostfix(treeNode<char> *node) {
    if (node != nullptr) {
        traversePostfix(node->right);
        traversePostfix(node->left);
        cout << node->data << " ";
    }
}

void expressionTree::infixPrint() {
    traverseInfix(root);
    cout << endl;
}

void expressionTree::prefixPrint() {
    traversePrefix(root);
    cout << endl;
}

void expressionTree::postfixPrint() {
    traversePostfix(root);
    cout << endl;
}

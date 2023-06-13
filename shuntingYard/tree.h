#ifndef TREE_H
#define TREE_H

#include "nodes.h"

class expressionTree {
    private:
        treeNode<char>* root;

        void traverseInfix(treeNode<char>*);
        void traversePrefix(treeNode<char>*);
        void traversePostfix(treeNode<char>*);

    public:
        expressionTree();
        ~expressionTree();

        bool empty();
        void setRoot(treeNode<char> *);

        void infixPrint();
        void prefixPrint();
        void postfixPrint();
};

#endif
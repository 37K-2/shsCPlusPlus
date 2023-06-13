#ifndef STACK_H
#define STACK_H

#include "nodes.h"

class nodeStack {
    private:
        llNode<char> *top;

    public:
        nodeStack();
        ~nodeStack();

        bool empty();
        void push(char);
        char pop();
        char peek();
};

class expressionStack {
    private:
        llNode<treeNode<char> *> *top;

    public:
        expressionStack();
        ~expressionStack();

        bool empty();
        void push(treeNode<char> *);
        treeNode<char> *pop();
        treeNode<char> *peek();
};

#endif 

//first stack is a stack used by the Shunting Yard Algorithm, and the second is for the binary espression tree

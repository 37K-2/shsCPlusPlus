#include "stacks.h"
nodeStack::nodeStack() {
    top = nullptr;
}

nodeStack::~nodeStack()
{
    linkedListNode<char> *current = top;
    while (current != nullptr) {
        linkedListNode<char> *temp = current->next;
        delete current;
        current = temp;
    }
    top = nullptr;
}

bool nodeStack::empty() {
    return (top == nullptr);
}

void nodeStack::push(char data) {
    linkedListNode<char> *node = new linkedListNode<char>(data);

    if (empty())
        top = node;
    else {
        node->next = top;
        top = node;
    }
}

char nodeStack::pop() {
    if (empty())
        return '\0';

    char data = top->data;
    linkedListNode<char> *temp = top;
    top = top->next;
    delete temp;
    return data;
}

char nodeStack::peek() {
    if (empty())
        return '\0';
    return top->data;
}

expressionStack::expressionStack()
{
    top = nullptr;
}

expressionStack::~expressionStack()
{
    linkedListNode<treeNode<char> *> *current = top;
    while (current != nullptr) {
        linkedListNode<treeNode<char> *> *temp = current->next;
        delete current;
        current = temp;
    }
    top = nullptr;
}

bool expressionStack::empty() {
    return (top == nullptr);
}

void expressionStack::push(treeNode<char> *data) {
    linkedListNode<treeNode<char> *> *node = new linkedListNode<treeNode<char> *>(data);

    if (empty())
        top = node;
    else {
        node->next = top;
        top = node;
    }
}

treeNode<char> *expressionStack::pop()
{
    if (empty())
        return nullptr;

    treeNode<char> *data = top->data;
    linkedListNode<treeNode<char> *> *temp = top;
    top = top->next;
    delete temp;
    return data;
}

treeNode<char> *expressionStack::peek()
{
    if (empty())
        return nullptr;
    return top->data;
}
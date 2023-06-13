#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "nodes.h"

using namespace std;

class outputQueue {
    private:
        linkedListNode<char>* front;
        linkedListNode<char>* rear;
    public:
        outputQueue();
        ~outputQueue();
        
        bool empty();
        void enqueue(char);
        char dequeue();
        char peek();
};

#endif

// first in first out and items will be dequed in same order when enqueued

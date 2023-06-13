#include "queue.h"
#include "nodes.h"

outputQueue::outputQueue() {
    front = nullptr;
    rear = nullptr;
}

outputQueue::~outputQueue() {
    linkedListNode<char> *current = front;
    while (current != nullptr) {
        linkedListNode<char> *temp = current->next;
        delete current;
        current = temp;
    }
    front = nullptr;
    rear = nullptr;
}

bool outputQueue::empty() {
    return (front == nullptr && rear == nullptr);
}

void outputQueue::enqueue(char data) {
    linkedListNode<char> *node = new linkedListNode<char>(data);

    if (empty())
        this->front = rear = node;
    else {
        rear->next = node;
        rear = node;
    }
}

char outputQueue::dequeue() {
    if (front == nullptr)
        return '\0';

    char data = front->data;
    linkedListNode<char> *temp = front;

    if (front == rear)
        front = rear = nullptr;
    else
        front = front->next;

    delete temp;
    return data;
}

char outputQueue::peek() {
    if (empty())
        return '\0';

    return front->data;
}
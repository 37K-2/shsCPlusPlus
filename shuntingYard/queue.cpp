#include "queue.h"
#include "nodes.h"

outputQueue::outputQueue() {
    front = nullptr;
    rear = nullptr;
}

outputQueue::~outputQueue() {
    llNode<char> *current = front;
    while (current != nullptr) {
        llNode<char> *temp = current->next;
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
    llNode<char> *node = new llNode<char>(data);

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
    llNode<char> *temp = front;

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
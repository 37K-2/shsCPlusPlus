#include <iostream>
#include <algorithm>

using namespace std;

class Heap{
private:
    int *heap;
    int heapSize;
    int arraySize;

    // left, right, and parent node of certain index
    int parent(int i);
    int left(int i);
    int right(int i);

    void swap(int &a, int &b); // swap two indicies
    void maxHeapify(int i); // reheap array at given index

public:
    Heap(int capacity);
    ~Heap();

    void insert(int value);
    int extractMax();

    void printHeap(int i, int depth); //top to bottom, right nodes are on top and left are on the bottom

    // getters
    int getMax() const { return heap[0]; }
    int getHeapSize() const { return heapSize; }
    bool isHeapFull() const { return heapSize == arraySize; }
    int peek(int i) const { return this->heap[i]; }
};

// max heap, where node is larger than the child
// uses insertion (new val and end of array and goes up), and extraction (takes large node and replaces root)

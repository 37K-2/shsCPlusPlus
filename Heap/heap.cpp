#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

#include "heap.h"

using namespace std;

Heap::Heap(int capacity){
    heap = new int[capacity];
    heapSize = 0;
    arraySize = capacity;
}

Heap::~Heap(){
    delete[] heap;
}

int Heap::parent(int i){
    return (i - 1) / 2;
}

int Heap::left(int i){
    return 2 * i + 1;
}

int Heap::right(int i){
    return 2 * i + 2;
}

void Heap::swap(int &a, int &b){
    // passing integerals by reference, as such they update globally
    int temp = a;
    a = b;
    b = temp;
}

void Heap::maxHeapify(int i){
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < heapSize && heap[l] > heap[i])
        largest = l;

    if (r < heapSize && heap[r] > heap[largest])
        largest = r;

    if (largest != i){
        swap(heap[i], heap[largest]);
        maxHeapify(largest);
    }
}

void Heap::insert(int val){
    if (heapSize == arraySize){
        cout << "Heap is full!" << endl;
        return;
    }

    heap[heapSize] = val; // insert val at end of array

    int i = heapSize;                         
    while (i > 0 && heap[i] > heap[parent(i)]){ // start at end of array and continue until at root or new val is in correct place
        swap(heap[i], heap[parent(i)]);
        i = parent(i); // Work backwards to the current node's parent.
    }

    heapSize++;
}

int Heap::extractMax(){
    if (heapSize == 0){
        cout << "Heap is empty!" << endl;
        return -1;
    }

    int max = heap[0];            // retrieve root node
    heap[0] = heap[heapSize - 1]; // set root to last in array
    heapSize--;
    maxHeapify(0); // reheap from top
    return max;
}

void Heap::printHeap(int i, int depth){
    if (i >= this->getHeapSize())
        return;

    // get left & right
    int right = 2 * i + 2;
    int left = 2 * i + 1;

    printHeap(right, depth + 1); // print children of right node

    // set indent from current node
    cout << setw(depth * 5) << ""; // add indent
    cout << heap[i] << endl;

    printHeap(left, depth + 1); // print children of left node
}

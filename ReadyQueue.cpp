#include <iostream>
#include "ReadyQueue.h"

// TODO: Add your implementation of ReadyQueue functions here

// constructor build an array queue with given size
ReadyQueue::ReadyQueue(int size) {
    queueSize = 0;
    arraySize = size;
    arr = new int[size];
}

// deconstructor
ReadyQueue::~ReadyQueue(){

}

// swaps two pcbs
void swapPCBs(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Add new PCB to the queue
void ReadyQueue::addPCB(int p) {
    
    // insert new pcb at the end of queue
    queueSize++;
    int i = queueSize - 1;
    arr[i] = p;
    
    //sort if priority is higher than parent pcb
    while (i > 0 && arr[i] > arr[(i-1)/2]) {
        swapPCBs(&arr[i], &arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

// Remove and return PCB with highest queue priority
int ReadyQueue::removePCB(){
  // return max priority pcb and remove from queue then resort queue
  int maxPriority = arr[0];
  arr[0] = arr[queueSize - 1];
  queueSize--;
  sortQueue(0);
  return maxPriority;
}

// recursive sorting starting from given index i
void ReadyQueue::sortQueue(int i){
    int higher = i;
    int left = (2*i + 1);
    int right = (2*i + 2);
    if (left < queueSize && arr[left] > arr[i])
        higher = left;
    if (right < queueSize && arr[right] > arr[i])
        higher = right;

    if (higher != i) {
        swapPCBs(&arr[i], &arr[higher]);
        sortQueue(higher);
    }

}

// Return the queue size
int ReadyQueue::size() {
  return queueSize;
}

// Displays content of the Queue
void ReadyQueue::display() {
  for (int i = 0; i < size(); i++) {
    //cout << returnID() << "\t" << returnPriority() << endl;
  }
}

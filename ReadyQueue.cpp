#include <iostream>
#include "ReadyQueue.h"
#include <PCB.h>

// TODO: Add your implementation of ReadyQueue functions here
// Add new PCB to the queue
void ReadyQueue::addPCB(PCB* pcbPtr) {
  
}

// Remove and return PCB with highest queue priority
void ReadyQueue::PCB* removePCB() {
  
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

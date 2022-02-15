#include <iostream>
#include "ReadyQueue.h"

using namespace std;
// TODO: Add your implementation of ReadyQueue functions here

// constructor build a pcb array queue with given size
ReadyQueue::ReadyQueue(int size) {
    queueSize = 0;
    PCB pcbArray[size];
}

// deconstructor
ReadyQueue::~ReadyQueue(){}

// swaps two pcbs
void swapPCBs(PCB *a, PCB *b) {
    PCB temp = *a;
    *a = *b;
    *b = temp;
}

// Add new PCB to the queue 
void ReadyQueue::addPCB(PCB p) {
    //set state to ready
    p.setReady();

    // insert new pcb at the end of queue
    queueSize++;
    int i = queueSize - 1;
    pcbArray[i] = p;

    //sort if priority is higher than parent pcb
    while (i > 0 && pcbArray[i].priority > pcbArray[(i-1)/2].priority) {
        swapPCBs(&pcbArray[i], &pcbArray[(i-1)/2]);
        i = (i-1)/2;
        }
}

// Remove and run PCB with highest queue priority
void ReadyQueue::removePCB(){
    //set state to running
    pcbArray[0].setRunning();
  // remove max priority pcb and remove from queue then resort queue
  //PCB maxPriority = pcbArray[0];
  pcbArray[0] = pcbArray[queueSize - 1];
  queueSize--;
  sortQueue(0);
}

// recursive sorting starting from given index i move highest priority to the top
void ReadyQueue::sortQueue(int i){
    int higher = i;
    int left = (2*i + 1);
    int right = (2*i + 2);
    if (left < queueSize && pcbArray[left].priority > pcbArray[i].priority)
        higher = left;
    if (right < queueSize && pcbArray[right].priority > pcbArray[higher].priority)
        higher = right;

    if (higher != i) {
        swapPCBs(&pcbArray[i], &pcbArray[higher]);
        sortQueue(higher);
    }

}

// Return the queue size
int ReadyQueue::size() {
  return queueSize;
}

// Displays content of the Queue
void ReadyQueue::display() {
if (size() == 0) { cout << "ReadyQueue is Now Empty\n"; return; }
   cout << "\nPCB queue: \n___________________________________\n" 
   << "ID \t Priority \t State" << endl;
  for (int i = 0; i < size(); i++) {
    cout << pcbArray[i].id << "\t" << pcbArray[i].priority << "\t" << pcbArray[i].state << endl;
  }
}

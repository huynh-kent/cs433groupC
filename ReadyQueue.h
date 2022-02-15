// Remember to add comments to your code
// ...

#pragma once

#include "PCB.h"


/**
 * ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue here such that the process with the highest priority
 * can be selected next.
 */

// function to swap two pcbs
void swapPCBs(PCB *a, PCB *b);

class ReadyQueue {
private:
int queueSize; //size of queue
PCB pcbArray[]; //pcb array

	
public:
// TODO: Implement the required functions. Add necessary member fields and functions

// constructor
ReadyQueue(int);
// deconstructor
~ReadyQueue();

// You may use different parameter signatures from the example below

// add a PCB representing a process into the ready queue.
void addPCB(PCB p);

// sort queue from given index i
void sortQueue(int i);

// remove and return the PCB with the highest priority from the queue
void removePCB();

// Returns the number of elements in the queue.
int size();

// Prints the queue contents to standard output.
void display();

};

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
void swapPCBs(int *a, int *b);

class ReadyQueue {
private:

int queueSize; //size of queue
int *arr; // pointer to elements in array queue
int arraySize; // size of array
	
public:
// TODO: Implement the required functions. Add necessary member fields and functions
// constructor
ReadyQueue(int arraySize);
// deconstructor
~ReadyQueue();
// You may use different parameter signatures from the example below

// add a PCB representing a process into the ready queue.
void addPCB(int p);

// sort queue from given index i
void sortQueue(int i);

// remove and return the PCB with the highest priority from the queue
int removePCB();

// Returns the number of elements in the queue.
int size();

// Prints the queue contents to standard output.
void display();

};

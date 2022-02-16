#include <cstdlib>
#include "PCB.h"
using namespace std;


// TODO: Add your implementation here

// Default Constructor
PCB::PCB() {
  state = NEW; //initialize the process state as NEW
  id = 100;
  priority = (rand() % 50) + 1;
}


// Constructor
PCB::PCB(int newID, int newPriority, ProcState newState) {
  state = newState; //initialize the process state as NEW
  id = newID;
  priority = newPriority;
}

// predesired ID constructor with random priority
PCB::PCB(int i){
  state = NEW;
  priority = (rand() % 50) + 1;
  id = i + 1;
}

PCB::PCB(double i){
  state = NEW;
  priority = (rand() % 50) + 1;
  uniqueID = i + 1;
}

// Destructor
//PCB::~PCB() {}

/*void PCB::setID() { 
  id;
}*/

/*
void PCB::setRandomPriority() {
  int randomPriority = rand() % 50 + 1; 
  priority = randomPriority;
}*/

// function to set PCB state to ready
void PCB::setReady() { state = READY; }

// function to set PCB state to running
void PCB::setRunning() { state = RUNNING;}

// Return PCB ID
int PCB::returnID() {   return id; }
	
// Return PCB priority
int PCB::returnPriority() {return priority; }

// Return state
ProcState PCB::returnState(){return state; }
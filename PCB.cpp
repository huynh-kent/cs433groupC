using namespace std;
#include "PCB.h"


// TODO: Add your implementation here

// Default Constructor
PCB::PCB() {
  ProcState state; //initialize the process state as NEW
  id = 0;
  priority = 0;
}


// Constructor
PCB::PCB(int newID, int newPriority, ProcState newState) {
  state = newState; //initialize the process state as NEW
  id = newID;
  priority = newPriority;
}

// Destructor
//PCB::~PCB() {
//}

//void PCB::setID(int newId) { id = newId; }

//void PCB::setPriority(int newPriority) { priority = newPriority; }

void PCB::setReady() { state = READY; }

void PCB::setRunning() { state = RUNNING;}

// Return PCB ID
int PCB::returnID() {   return id; }
	
// Return PCB priority
int PCB::returnPriority() {return priority; }

// Return state
ProcState PCB::returnState(){ return state; }

using namespace std;
#include "PCB.h"

// TODO: Add your implementation here

// Default Constructor
PCB::PCB() {
  ProcState = NEW; //initialize the process state as NEW
  id = 0;
  priority = 0;
}

// Constructor
PCB::PCB(x, p) {
  ProcState = NEW; //initialize the process state as NEW
  id = x;
  priority = p;
}

// Destructor
PCB::~PCB() {
}

void PCB::setID(int newId)
{
    id = newId;
}

void PCB::setPriority(int newPriority)
{
    intPriority = newPriority;
}

void PCB::setState(ProcState newState)
{
    state = newState;
}

// Return PCB ID
int PCB::returnID() {
  return id;
}
	
// Return PCB priority
int PCB::returnPriority() {
 return priority; 
}

// Return state
ProcState PCB::getState()
{
    return state;
}

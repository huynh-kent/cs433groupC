using namespace std;
#include "PCB.h"

// TODO: Add your implementation here

// Constructor
PCB::PCB(x, p) {
  ProcState = NEW; //initialize the process state as NEW
  id = x;
  priority = p;
}

// Destructor
PCB::~PCB() {
}

// Sets PCB state as READY
void PCB::stateReady() {
  ProcState = READY;
}

// Sets PCB state as RUNNING
void PCB::stateRunning() {
  ProcState = RUNNING;
}

// Sets PCB state as WAITING
void PCB::stateWaiting() {
  ProcState = WAITING;
}

// Sets PCB state as TERMINATED
void PCB::stateTerminated() {
  ProcState = TERMINATED;
}

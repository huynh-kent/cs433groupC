#pragma once
using namespace std;

// Remember to add comments to your code
// ...

// enum class of process state
// A process (PCB) in ready queue should be in READY state

enum ProcState {NEW, READY, RUNNING, WAITING, TERMINATED};

/* 
Process control block(PCB) is a data structure representing a process in the system.
A process should have at least an ID and a state(i.e.NEW, READY, RUNNING, WAITING or TERMINATED).
It may also have other attributes, such as scheduling information (e.g. priority)
*/

class PCB {
public:
    // The unique process ID
	int id;
    // The priority of a process valued between 1-50. Larger number represents higher priority
	int priority;
	// The current state of the process.
	// A process in the ReadyQueue should be in READY state
	ProcState state;
	double uniqueID;
	// TODO: Add constructor and other necessary functions for the PCB class
	
	//Default constructor
	PCB();

	//Insert constructor
	PCB(int, int, ProcState);
	
	//ID generated constructor
	PCB(int);
	PCB(double);

	//Deconstructor
	//~PCB();
	
	// Function to set ID
	void setID();
	
	// Function to set priority
	void setRandomPriority();
	
	// Function to set to ready state
	void setReady();

	// Function to set running state
	void setRunning();
	
	// Function to return ID
	int returnID();
	
	// Function to return priority
	int returnPriority();
	
	// Function to return state
	ProcState returnState();
};
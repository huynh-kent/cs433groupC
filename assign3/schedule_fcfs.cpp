#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

#include <queue> // Header-file for queue
using namespace std;

// create head
struct node *head = NULL;

// add a new task to the list of tasks
 void add(char *name, int priority, int burst) 
{
	// TODO: add your implementation here

	// create task from given data
	Task *temptask = (Task *) malloc(sizeof(Task));
	temptask->name = name;
	temptask->priority = priority;
	temptask->burst = burst;


	// insert task into list calling insert function
	if (head == NULL) 
		{ insert(&head, temptask);}
	else 
		{ insertLast(&head, temptask); }
}

/**
 *  * Run the FCFS scheduler
 *   */
void schedule() 
{
	int turnaround = 0, waiting = 0;
	Task *runThisTask;

	while (head != NULL)
	{
		// run task
		runThisTask = head->task;
		run(runThisTask, runThisTask->burst);

		// calculate turnaround and waiting times and to print list
		turnaround += runThisTask->burst;
		waiting = turnaround - runThisTask->burst;
		addPrint(runThisTask->name, turnaround, waiting);

		// remove task from list
		remove(&head, runThisTask);
	}
	
	// finished running tasks
	printf("----------No more tasks----------\n");

}

void scheduleRR(char *argQuantum)
{}

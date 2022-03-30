#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

// create a head
struct node *head = NULL;

// add a new task to the list of tasks
 void add(char *name, int priority, int burst) 
{
	// create task to add to list
	Task *temptask = (Task *) malloc(sizeof(Task));
	temptask->name = name;
	temptask->priority = priority;
	temptask->burst = burst;

	// if list empty insert task as first
	if (head == NULL) 
		{ insert(&head, temptask);}
	else // insert at end of list
		{ insertLast(&head, temptask); }
}

/**
 *  * Run the RR scheduler
 *   */

// not using this scheduler for RR
void schedule() { 
	printf("No Quantum Given or Incorrect Format\n"); 
}

// using this scheduler for RR
void scheduleRR(char *argQuantum)
{
	int turnaround = 0, run_time;
	int quantum = atoi(argQuantum);		// convert quantum arg -> int
	Task *runThisTask;
	struct node *temp;

	while (head != NULL)
	{
		runThisTask = head->task;
		temp = head;

		if (runThisTask->burst > quantum) { // if task uses the whole quantum slice
			run_time = quantum; }
		else {	// if task only uses portion of quantum slice
			run_time = runThisTask->burst; }
			
		run(runThisTask, run_time);

		// update tasks' burst time after running
		runThisTask->burst -= run_time;
		// keep track of total time elapsed
		turnaround += run_time;

		if (runThisTask->burst > 0) // task not finished
		{
			runThisTask->waiting_time -= run_time ;
			insertLast(&temp, runThisTask);	// add back to end of list with new burst time
		}
		else // task finishes
		{	// calculate turnaround/waiting time for task
			runThisTask->waiting_time += (turnaround - run_time) ;
			addPrint(runThisTask->name, turnaround, runThisTask->waiting_time);	// add to finished tasks print list with turnaround/wait times
		}
		// remove task from list
		remove(&head, runThisTask);
	}

	// finished running tasks
	printf("----------No more tasks----------\n");
}

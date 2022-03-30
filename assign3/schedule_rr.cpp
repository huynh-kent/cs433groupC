#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;

// add a new task to the list of tasks
 void add(char *name, int priority, int burst) 
{
	Task *temptask = (Task *) malloc(sizeof(Task));
	temptask->name = name;
	temptask->priority = priority;
	temptask->burst = burst;

	if (head == NULL) 
		{ insert(&head, temptask);}
	else 
		{ insertLast(&head, temptask); }
}

/**
 *  * Run the RR scheduler
 *   */
void schedule() { printf("No Quantum Given or Incorrect Format\n"); }

void scheduleRR(char *argQuantum)
{
	int turnaround = 0, run_time;
	int quantum = atoi(argQuantum);
	Task *runThisTask;
	struct node *temp;

	while (head != NULL)
	{
		runThisTask = head->task;
		temp = head;

		if (runThisTask->burst > quantum)
		{ run_time = quantum; }
		else
		{ run_time = runThisTask->burst; }

		run(runThisTask, run_time);

		runThisTask->burst -= run_time;
		turnaround += run_time;

		if (runThisTask->burst > 0) 
		{
			//turnaround += run_time;
			runThisTask->waiting_time -= run_time ;
			insertLast(&temp, runThisTask);
		}
		else
		{
			//turnaround += run_time;
			runThisTask->waiting_time += (turnaround - run_time) ;
			addPrint(runThisTask->name, turnaround, runThisTask->waiting_time);
		}
	
		remove(&head, runThisTask);
	}
}

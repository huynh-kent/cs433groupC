#include <stdlib.h>
#include <stdio.h>
#include <queue>

#include "task.h"
#include "list.h"
#include "cpu.h"

// create head
struct node *head = NULL;

// add a new task to the list of tasks
 void add(char *name, int priority, int burst) 
{
	// create task
	Task *temptask = (Task *) malloc(sizeof(Task));
	temptask->name = name;
	temptask->priority = priority;
	temptask->burst = burst;
	// insert task
	insert(&head, temptask);
}

/**
 *  * Run the Priority scheduler
 *   
 */
void schedule() 
{
	int turnaround = 0, waiting = 0;
	Task *runThisTask;
	struct node *temp;

	while (head != NULL)
	{
		temp = head->next;
		runThisTask = head->task;

		// run task with highest priority
		while (temp != NULL)
		{
			if (temp->task->priority <= runThisTask->priority)
				{	runThisTask = temp->task;	}
			temp = temp->next;
		}
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

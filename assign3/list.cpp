/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"

// init print head
struct node *print_head = NULL;

// add a new task to end of list of tasks
void insertLast(struct node **head, Task *newTask)
{
    // create node for task
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->task = newTask;
    newNode->next = NULL;

    // add node if list is empty
    if (*head == NULL) { *head = newNode; }
    else // add to end of list
    {
        struct node *tail = *head;

        // make lastnode next address null
        while (tail->next != NULL)
        {   tail = tail->next;  }
        
        // add new node at end of list
        tail->next = newNode;
    }

}


// add a new task to the list of tasks
void insert(struct node **head, Task *newTask) {
    // add the new task to the list 
    struct node *newNode = (struct node *) malloc(sizeof(struct node));

    newNode->task = newTask;
    newNode->next = *head;
    *head = newNode;
}

// delete the selected task from the list
void remove(struct node **head, Task *task) {
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}

// add tasks to a separate printing list with their turnaround/waiting time
void addPrint(char *name, int turnaround, int waiting)
{
	Task *finishTask = (Task *) malloc(sizeof(Task));
	finishTask->name = name;
	finishTask->turnaround_time = turnaround;
	finishTask->waiting_time = waiting;

	insert(&print_head, finishTask);
}


// print turnaround and waiting time of each task
void printTimes()
{
    struct node *temp;
    temp = print_head;
    int total_turnaround = 0, total_waiting = 0, task_count = 0;

    // print all finished tasks
    while (temp != NULL)
    {
        printf("[%s], turnaround time = %d, waiting time = %d\n", temp->task->name, temp->task->turnaround_time, temp->task->waiting_time);
        total_turnaround += temp->task->turnaround_time;
        total_waiting += temp->task->waiting_time;
        temp = temp->next;
        task_count++;
    }

    // average turnaround time and average waiting time
    printf("---------------------------------\n");
    printf("Average Turnaround Time - %.2f\nAverage Waiting Time - %.2f\n", (float(total_turnaround)/task_count), (float(total_waiting)/task_count));
}
/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

struct node {
    Task *task;
    struct node *next;
};

// insert and delete operations.
void insert(struct node **head, Task *task);
void remove(struct node **head, Task *task);
void traverse(struct node *head);
void insertLast(struct node **head, Task *task);
void addPrint(char *name, int turnaround, int waiting);
void printTimes();
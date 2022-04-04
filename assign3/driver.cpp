/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>

#include "task.h"
#include "list.h"
#include "schedulers.h"


#define SIZE    100

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "CS 433 Programming assignment 3" << std::endl;
    std::cout << "Authors: Kent Huynh, Daniel Martinez, and Raymond Quach" << std::endl;
    std::cout << "Date: 04/05/2022" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description : Schedule a set of Tasks with different scheduling algorithms." << std::endl;
    std::cout << "FCFS, SJF, Priority, and RR" << std::endl;
    std::cout << "Returning each task's turnaround and waiting time, as well as the average for that specific scheduling algorithm." << std::endl;
    std::cout << "Compile the specific algorithm using 'make (Enter Algorithm Here)' with the algorithms being 'fcfs', 'sjf', 'Priority', 'rr'." << std::endl;
    std::cout << "For RR, to enter the desired Quantum Slice, enter it as an argument after the scheduler file." << std::endl;
    std::cout << "Example: './rr scheduler.txt 9' for a Quantum Slice of 9." << std::endl;
    std::cout << "=================================" << std::endl;

    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;


    in = fopen(argv[1],"r");

    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add(name,priority,burst);

        free(temp);
    }

    fclose(in);

    // if there is quantum arguement
    if (argc == 3) { // invoke special RR scheduler
        scheduleRR(argv[2]); }
    else { // invoke the normal scheduler 
        schedule(); }

    // print times of tasks
    printTimes();

    return 0;
}

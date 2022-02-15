// Remember to add comments to your code

#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include "ReadyQueue.h"

int main(int argc, char* argv[]) {
	//Print basic information about the program
	std::cout << "CS 433 Programming assignment 1" << std::endl;
	std::cout << "Author: Kent Huynh, Daniel Martinez, and Raymond Quach" << std::endl;
	std::cout << "Date: 02/09/2022" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Program to implement a priority ready queue of processes" << std::endl;
	std::cout << "=================================" << std::endl;

	// TODO: Add your code for Test 1
	std::cout << "Performing Test 1" << std::endl;
	
	// Call readyQueue
	ReadyQueue q1(50);
	
	//TODO: add processes 14, 1, 28, 39 and 18 to q1. Display the content of q1
	PCB process1(14, 14, NEW); 
	PCB process2(1, 1, NEW); 
	PCB process3(28, 28, NEW); 
	PCB process4(39, 39, NEW); 
	PCB process5(18, 18, NEW); 
	
	//TODO: remove one process with the highest priority from q1 and display q1.
	q1.remove();
	q1.display();
	
	//TODO: add additional processes 48, 10, 31 and 19 into q1, and display q1.
	PCB process6(48, 48, NEW); 
	PCB process7(10, 10, NEW); 
	PCB process8(31, 31, NEW); 
	PCB process9(19, 19, NEW);
	
	//TODO: remove one process with the highest priority from q1 and display q1.
	q1.remove();
	q1.display();
	
	//TODO: add additional processes 29, 41, 18 and 46 to q1 and display q1.
	PCB process10(29, 29, NEW); 
	PCB process11(41, 41, NEW); 
	PCB process12(18, 18, NEW); 
	PCB process13(46, 46, NEW);
	
	//TODO: One by one remove the process with the highest priority from the queue q1 and display the queue after each removal.


	// TODO: Add your code for Test 2
	std::cout << "Performing Test 2" << std::endl;
	struct timespec start, end;
        //start timer 
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < 1000000; i++) {
       		//TODO: add or remove a process with equal probabilty
	}
	//end timer
	clock_gettime(CLOCK_MONOTONIC, &end);
  
    	//Calculating total time taken by the program.
    	double time_taken = (end.tv_sec + end.tv_nsec*1e-9) - (start.tv_sec + start.tv_nsec*1e-9);
	printf("Test 2 run time = %f seconds\n", time_taken);
}

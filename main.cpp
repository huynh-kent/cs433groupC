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
	ReadyQueue q1(50);   // first test
	//ReadyQueue q2(100);  // second test
	
	//TODO: add processes 14, 1, 28, 39 and 18 to q1. Display the content of q1
	PCB p1(14, 14, NEW);
	q1.addPCB(p1);
	PCB p2(1, 1, NEW);
	q1.addPCB(p2); 
	PCB p3(28, 28, NEW);
	q1.addPCB(p3); 
	PCB p4(39, 39, NEW); 
	q1.addPCB(p4);
	PCB p5(18, 18, NEW);
	q1.addPCB(p5); 
	q1.display();

	
	//TODO: remove one process with the highest priority from q1 and display q1.
	q1.removePCB();
	q1.display();

	//TODO: add additional processes 48, 10, 31 and 19 into q1, and display q1.
	PCB p6(48, 48, NEW); 
	q1.addPCB(p6);
	PCB p7(10, 10, NEW); 
	q1.addPCB(p7);
	PCB p8(31, 31, NEW); 
	q1.addPCB(p8);
	PCB p9(19, 19, NEW);
	q1.addPCB(p9);
	
	//TODO: remove one process with the highest priority from q1 and display q1.
	q1.removePCB();
	q1.display();
	
	//TODO: add additional processes 29, 41, 18 and 46 to q1 and display q1.
	PCB p10(29, 29, NEW); 
	q1.addPCB(p10);
	PCB p11(41, 41, NEW); 
	q1.addPCB(p11);
	PCB p12(18, 18, NEW); 
	q1.addPCB(p12);
	PCB p13(46, 46, NEW);
	q1.addPCB(p13);

	//TODO: One by one remove the process with the highest priority from the queue q1 and display the queue after each removal.
	while (q1.size() != 0){
		q1.removePCB();
		q1.display();
	}

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

// Remember to add comments to your code

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include "pagetable.h"
#include <chrono>

using namespace std;

// Check if an integer is power of 2
bool isPowerOfTwo(unsigned int x)
{
	/* First x in the below expression is for the case when x is 0 */
	return x && (!(x & (x - 1)));
}

int main(int argc, char* argv[]) {
	//Print basic information about the program
	std::cout << "=================================================================" << std::endl;
	std::cout << "CS 433 Programming assignment 5" << std::endl;
	std::cout << "Author: xxxxxx and xxxxxxx" << std::endl;
	std::cout << "Date: xx/xx/20xx" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Program to simulate different page replacement algorithms" << std::endl;
	std::cout << "=================================================================\n" << std::endl;

	if (argc < 3) {
		// user does not enter enough parameters
		std::cout << "You have entered too few parameters to run the program.  You must enter" << std::endl
			<< "two command-line arguments:" << std::endl
			<< " - page size (in bytes): between 256 and 8192, inclusive" << std::endl
			<< " - physical memory size (in megabytes): between 4 and 64, inclusive" << std::endl;
		exit(1);
	}
	
	// Page size and Physical memory size 
	// Their values should be read from command-line arguments, and always a power of 2
	unsigned int page_size = atoi(argv[1]);
	if(!isPowerOfTwo(page_size))
	{
		std::cout << "You have entered an invalid parameter for page size (bytes)" << std::endl
			<< "  (must be an power of 2 between 256 and 8192, inclusive)." << std::endl;
		return 1;
	}
	unsigned int phys_mem_size = atoi(argv[2]) << 20; // convert from MB to bytes
	if(!isPowerOfTwo(phys_mem_size))
	{
		std::cout << "You have entered an invalid parameter for physical memory size (MB)" << std::endl
			<< "  (must be an even integer between 4 and 64, inclusive)." << std::endl;
		return 1;
	}

	// calculate number of pages and frames;
	int logic_mem_bits = 27;		// 27-bit logical memory (128 MB logical memory assumed by the assignment)
	int phys_mem_bits = std::log2(phys_mem_size);		// Num of bits for physical memory addresses, calculated from physical memory size, e.g. 24 bits for 16 MB memory
	int page_offset_bits = std::log2(page_size);				// Num of bits for page offset, calculated from page size, e.g. 12 bits for 4096 byte page
	// Number of pages in logical memory = 2^(logic_mem_bits - page_bit)
	int num_pages = 1 << (logic_mem_bits - page_offset_bits);
	// Number of free frames in physical memory = 2^(phys_mem_bits - page_offset_bits)
	int num_frames = 1 << (phys_mem_bits - page_offset_bits);
	
	std::cout << "Page size = " << page_size << " bytes" << std::endl;
	std::cout << "Physical Memory size = " << phys_mem_size << " bytes" << std::endl;
	std::cout << "Number of pages = " << num_pages << std::endl; 
	std::cout << "Number of physical frames = " << num_frames << std::endl;


	clock_t start, stop; // timer
	// Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
	std::cout <<"\n================================Test 1==================================================\n";
	// TODO: Add your code here for test 1 that prints out logical page #, frame # and whether page fault for each logical address
	PageTable test1;

	// read addresses from file
	ifstream small_refs("small_refs.txt");
	string address;
	int page, log, frame;
	bool fault;


	while (getline(small_refs, address))
	{
		log = stoi(address);
		page = log / page_size;
		int temp = test1.checkTable(page);
		if (temp!=-1)
		{
			frame = test1.table[temp].frame_num;
			fault = false;
		}
		else 
		{
			frame = test1.frame_num_count;
			fault = true;
			test1.frame_num_count++;
			test1.fault_count++;
		}
		PageEntry newPage(log, page, frame, fault);
		test1.table.push_back(newPage);
		test1.ref_count++;
	}

	test1.printTable(test1.ref_count, test1.fault_count, test1.replace_count);
	test1.table.empty();

	// Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
	std::cout <<"\n================================Test 2==================================================\n";
	ifstream fifo_refs("large_refs.txt");
	string addr_fifo;
	PageTable fifo;

	std::cout << "****************Simulate FIFO replacement****************************" << std::endl;
	// TODO: Add your code to calculate number of page faults using FIFO replacement algorithm	
	start = clock();

	while (getline(fifo_refs, addr_fifo))
	{
		log = stoi(addr_fifo);
		page = log / page_size;
		int temp = fifo.checkTable(page);
		if (temp!=-1)
		{
			frame = fifo.table[temp].frame_num;
			fault = false;
		}
		else if (fifo.table.size() == num_frames)
		{
			fault = true;
			fifo.fault_count++;

			// find victim
			int victim = fifo.fifo_n_lru_count;
			fifo.fifo_n_lru_count++;
			fifo.fifo_n_lru_count %= num_frames;

			// make page with victim's frame
			frame = fifo.table[victim].frame_num;
			PageEntry newPage(log, page, frame, fault);

			// replace victim page
			fifo.table[victim] = newPage;
			fifo.replace_count++;
		}
		else 
		{
			frame = fifo.frame_num_count%num_frames;
			fault = true;
			fifo.frame_num_count++;
			fifo.fault_count++;
			PageEntry newPage(log, page, frame, fault);
			fifo.table.push_back(newPage);
		}
		
		
		fifo.ref_count++;
	}

	fifo.printReplacementStats(fifo.ref_count, fifo.fault_count, fifo.replace_count);
	fifo.table.empty();
	stop = clock();
	printf("Time Taken: %.6f seconds\n", ((float) stop - start)/CLOCKS_PER_SEC);
	// TODO: print the statistics and run-time

	std::cout << "****************Simulate Random replacement****************************" << std::endl;
	// TODO: Add your code to calculate number of page faults using Random replacement algorithm
	// TODO: print the statistics and run-time
	ifstream rand_refs("large_refs.txt");
	PageTable rand_table;
	string addr_rand;

	start = clock();

	while (getline(rand_refs, addr_rand))
	{
		log = stoi(addr_rand);
		page = log / page_size;
		int temp = rand_table.checkTable(page);
		if (temp!=-1)
		{
			frame = rand_table.table[temp].frame_num;
			fault = false;
		}
		else if (rand_table.table.size() == num_frames)
		{
			fault = true;
			rand_table.fault_count++;

			// find random victim
			int victim = rand() % num_frames;

			// make page with victim's frame
			frame = rand_table.table[victim].frame_num;
			PageEntry newPage(log, page, frame, fault);

			// replace victim page
			rand_table.table[victim] = newPage;
			rand_table.replace_count++;
		}
		else 
		{
			frame = rand_table.frame_num_count%num_frames;
			fault = true;
			rand_table.frame_num_count++;
			rand_table.fault_count++;
			PageEntry newPage(log, page, frame, fault);
			rand_table.table.push_back(newPage);
		}
		rand_table.ref_count++;
	}
	rand_table.printReplacementStats(rand_table.ref_count, rand_table.fault_count, rand_table.replace_count);
	stop = clock();
	printf("Time Taken: %.6f seconds\n", ((float) stop - start)/CLOCKS_PER_SEC);

	std::cout << "****************Simulate LRU replacement****************************" << std::endl;
	// TODO: Add your code to calculate number of page faults using LRU replacement algorithm
	// TODO: print the statistics and run-time
	ifstream lru_refs("large_refs.txt");
	PageTable lru;
	string addr_lru;

	start = clock();

	while (getline(lru_refs, addr_lru))
	{
		log = stoi(addr_lru);
		page = log / page_size;
		int temp = lru.checkTable(page);
		int victim;

		if (temp!=-1)
		{
			frame = lru.table[temp].frame_num;
			fault = false;
			lru.table[temp].lru_index = lru.lru_line; 
		}
		else if (lru.table.size() == num_frames)
		{
			fault = true;
			lru.fault_count++;

			// find victim
			// check if page not recently used
			if (lru.table[lru.fifo_n_lru_count].valid == false)
			{
				victim = lru.fifo_n_lru_count;
				lru.fifo_n_lru_count++;
				lru.fifo_n_lru_count %= num_frames;
			}
			// if not search for not recently used page
			else
			{
				victim = lru.checkLRU();
			}


			// make page with victim's frame
			frame = lru.table[victim].frame_num;
			PageEntry newPage(log, page, frame, fault, lru.lru_line);

			// replace victim page
			lru.table[victim] = newPage;
			lru.replace_count++;
		}
		else
		{
			frame = lru.frame_num_count%num_frames;
			fault = true;
			lru.frame_num_count++;
			lru.fault_count++;
			PageEntry newPage(log, page, frame, fault, lru.lru_line);
			lru.table.push_back(newPage);
		}
		lru.ref_count++;
	}
	lru.printReplacementStats(lru.ref_count, lru.fault_count, lru.replace_count);
	stop = clock();
	printf("Time Taken: %.6f seconds\n", ((float) stop - start)/CLOCKS_PER_SEC);



}

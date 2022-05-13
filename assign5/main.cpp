// Remember to add comments to your code

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include "pagetable.h"
#include <chrono>
#include <algorithm>

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
	std::cout << "CS 433 Programming Assignment 5" << std::endl;
	std::cout << "Author: Kent Huynh, Daniel Martinez, and Raymond Quach" << std::endl;
	std::cout << "Date: 05/12/2022" << std::endl;
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

	std::cout <<"\n================================Test 1==================================================\n";
	// read addresses from file
	PageTable test1;
	ifstream small_refs("small_refs.txt");
	string address;
	int page, log, frame;
	bool fault;

	// for each page ref in file
	while (getline(small_refs, address))
	{
		// set/calc log, page
		log = stoi(address);
		page = log / page_size;

		// check if page in table
		int temp = test1.checkTable(page);

		// if page in table
		// find/set frame&fault values
		if (temp!=-1)
		{
			frame = test1.table[temp].frame_num;
			fault = false;
		}
		// if table not full and page not in table
		else 
		{
			frame = test1.frame_num_count;
			fault = true;
			test1.frame_num_count++;
			test1.fault_count++;
		}
		// create page with values and add to table
		PageEntry newPage(log, page, frame, fault);
		test1.table.push_back(newPage);
		test1.ref_count++;
	}

	// print stats and empty table
	test1.printTable(test1.ref_count, test1.fault_count, test1.replace_count);
	test1.table.empty();


	std::cout <<"\n================================Test 2==================================================\n";

	std::cout << "****************Simulate FIFO replacement****************************" << std::endl;
	// read address from file
	ifstream fifo_refs("large_refs.txt");
	string addr_fifo;
	PageTable fifo;

	// start timer
	start = clock();

	// for each line in file
	while (getline(fifo_refs, addr_fifo))
	{
		// set/calc address & page files
		log = stoi(addr_fifo);
		page = log / page_size;

		// check if page in table
		int temp = fifo.checkTable(page);

		// if in table
		if (temp!=-1)
		{
			fifo.table[temp].valid = false;
		}

		// if table is full and page not in table
		else if (fifo.table.size() == num_frames)
		{
			// increment fault
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

		// table not full and page not in table
		else 
		{
			frame = fifo.frame_num_count%num_frames;
			fault = true;
			fifo.frame_num_count++;
			fifo.fault_count++;

			// add page to table
			PageEntry newPage(log, page, frame, fault);
			fifo.table.push_back(newPage);
		}
		fifo.ref_count++;
	}

	// print stats and empty table
	fifo.printReplacementStats(fifo.ref_count, fifo.fault_count, fifo.replace_count);
	fifo.table.empty();
	stop = clock();
	printf("Time Taken: %.6f seconds\n", ((float) stop - start)/CLOCKS_PER_SEC);

	std::cout << "****************Simulate Random replacement****************************" << std::endl;

	// read from ref file
	ifstream rand_refs("large_refs.txt");
	PageTable rand_table;
	string addr_rand;

	// start timer
	start = clock();

	// for each line in file
	while (getline(rand_refs, addr_rand))
	{
		// set/calculate address and page values
		log = stoi(addr_rand);
		page = log / page_size;

		// check if page in table
		int temp = rand_table.checkTable(page);

		// if page exists in table
		if (temp!=-1)
		{
			rand_table.table[temp].valid = false;
		}

		// if table is full and page not in table
		else if (rand_table.table.size() == num_frames)
		{
			// increment fault
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

		// if table is not full and page not in table
		else 
		{
			frame = rand_table.frame_num_count%num_frames;
			fault = true;
			rand_table.frame_num_count++;
			rand_table.fault_count++;

			// add page to table
			PageEntry newPage(log, page, frame, fault);
			rand_table.table.push_back(newPage);
		}
		rand_table.ref_count++;
	}

	// print stats and empty table
	rand_table.printReplacementStats(rand_table.ref_count, rand_table.fault_count, rand_table.replace_count);
	rand_table.table.empty();
	stop = clock();
	printf("Time Taken: %.6f seconds\n", ((float) stop - start)/CLOCKS_PER_SEC);

	std::cout << "****************Simulate LRU replacement****************************" << std::endl;

	// read addresses from refs file
	ifstream lru_refs("large_refs.txt");
	PageTable lru;
	string addr_lru;

	// set up LRU frame list
	lru.setupFrameList(num_frames);

	// start timer
	start = clock();

	// for each page ref in file
	while (getline(lru_refs, addr_lru))
	{
		// set/calculate address and page values
		log = stoi(addr_lru);
		page = log / page_size;

		// check if page is in table
		int temp = lru.checkTable(page);

		int victim;
		
		// if page exist in table
		if (temp!=-1)
		{
			// set to not fault and get frame
			lru.table[temp].valid = false;
			frame = lru.table[temp].frame_num;

			// move frame to end of LRU list
			lru.frame_list.erase(find(lru.frame_list.begin(),lru.frame_list.end(), frame));
			lru.frame_list.push_back(frame);
		}
		// if table is full
		else if (lru.table.size() == num_frames)
		{
			// increment faults
			fault = true;
			lru.fault_count++;

			// find least recently used frame
			frame = lru.frame_list.front();
			// move frame to end of LRU list
			lru.frame_list.erase(find(lru.frame_list.begin(),lru.frame_list.end(), frame));
			lru.frame_list.push_back(frame);

			// find victim index
			victim = lru.checkLRU(frame);

			// make replacement page
			PageEntry newPage(log, page, frame, fault);

			// replace victim page
			lru.table[victim] = newPage;
			lru.replace_count++;
		}
		// table not full yet
		else
		{
			frame = lru.frame_num_count%num_frames;
			fault = true;
			lru.frame_num_count++;
			lru.fault_count++;

			// add page to table
			PageEntry newPage(log, page, frame, fault);
			lru.table.push_back(newPage);
		}
		lru.ref_count++;
	}

	// print stats
	lru.printReplacementStats(lru.ref_count, lru.fault_count, lru.replace_count);
	stop = clock();
	printf("Time Taken: %.6f seconds\n", ((float) stop - start)/CLOCKS_PER_SEC);
}

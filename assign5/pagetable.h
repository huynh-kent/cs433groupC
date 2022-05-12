#pragma once
#include <vector>
using namespace std;

// A page table entry
class PageEntry
{
public:
	// logical address
	int log_addr;
	// page number
	int page_num;
	// Physical frame number for a given page
	int frame_num;
	// valid bit represents whether a page is in the physical memory
	bool valid;

	int lru_index;

	// default constructor
	PageEntry();

	// constructor
	PageEntry(int log_addr, int page_num, int frame_num, bool valid);
	PageEntry(int log_addr, int page_num, int frame_num, bool valid, int lru_index);
};


/**
 * \brief A page table is like an array of page entries. The size of the page table should equal to the number of pages in logical memory
 */
class PageTable
{
public:
	// TODO: Add your implementation of the page table here
	int page_size;
	int mem_size;
	int frame_num_count;
	int ref_count;
	int fault_count;
	int replace_count;
	int fifo_n_lru_count; 
	int lru_line;

	vector<PageEntry> table;
	// function/algorithm prototypes
	PageTable();
	void createTable(int table_size);
	int checkTable(int page_num);
	void printTable(int ref_count, int fault_count, int replace_count);
	void printReplacementStats(int ref_count, int fault_count, int replace_count);
	int checkLRU();
};

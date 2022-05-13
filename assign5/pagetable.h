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

	// default constructor
	PageEntry();
	// constructor
	PageEntry(int log_addr, int page_num, int frame_num, bool valid);
};


class PageTable
{
public:
	int frame_num_count;	// frame index counter
	int ref_count;			// total references count
	int fault_count;		// total fault count
	int replace_count;		// total replacements count
	int fifo_n_lru_count;	// count variable for fifo and lru

	vector<PageEntry> table;	// vector of page table
	vector<int> frame_list;		// vector of LRU frame list

	PageTable();	// default constructor

	int checkTable(int page_num);
	void printTable(int ref_count, int fault_count, int replace_count);
	void printReplacementStats(int ref_count, int fault_count, int replace_count);
	void setupFrameList(int num_frames);
	int checkLRU(int frame);
};

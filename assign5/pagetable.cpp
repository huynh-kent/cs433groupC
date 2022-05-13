#include "pagetable.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// page entry default constructor
PageEntry::PageEntry()
{
    log_addr = 0;
    page_num = 0;
    frame_num = 0;
    valid = false;
}

// page entry constructor 
PageEntry::PageEntry(int entry_log_addr, int page, int frame, bool fault)
{
    log_addr = entry_log_addr;
    page_num = page;
    frame_num = frame;
    valid = fault;
}

// page table default constructor
PageTable::PageTable()
{ 
    frame_num_count = 0;
    ref_count = 0;
    fault_count = 0;
    replace_count = 0;
    fifo_n_lru_count = 0;
}

// print table
void PageTable::printTable(int ref_count, int fault_count, int replace_count)
{
    for (int i = 0; i < table.size(); i++)
    {
        printf("Logical Address: %d,    Page Number: %d,    Frame Number = %d,  Is Page Fault? %d\n", table.at(i).log_addr, table.at(i).page_num, table.at(i).frame_num, table.at(i).valid);
    }
    printf("# of References: %d\n", ref_count);
    printf("# of Page Faults: %d\n", fault_count);
    printf("# of Page Replacements: %d\n", replace_count);
}

// print stats
void PageTable::printReplacementStats(int ref_count, int fault_count, int replace_count)
{
    printf("# of References: %d\n", ref_count);
    printf("# of Page Faults: %d\n", fault_count);
    printf("# of Page Replacements: %d\n", replace_count);

}

// check table if page in main memory
// if in memory, return its index
int PageTable::checkTable(int page)
{
    for (int index = 0; index < table.size(); index++)
    {
        if (table.at(index).page_num == page)
        { 
            return index;
        }
    }
    return -1;
}

// create frame list for LRU
void PageTable::setupFrameList(int num_frames)
{
    for (int i = 0; i < num_frames; ++i)
    {
        frame_list.push_back(i);
    }
}

// check for LRU page and return its index 
int PageTable::checkLRU(int frame)
{
    for (int i = 0; i < table.size(); i++)
    {
        if (table.at(i).frame_num == frame)
        {           
            return i;
        }
    }
}
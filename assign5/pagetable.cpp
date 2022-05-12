#include "pagetable.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// TODO: Add your implementation of PageTable

// page entry default constructor
PageEntry::PageEntry()
{
    log_addr = 0;
    page_num = 0;
    frame_num = 0;
    valid = false;
    lru_index = 0;
}

// page entry constructor 
PageEntry::PageEntry(int entry_log_addr, int page, int frame, bool fault)
{
    log_addr = entry_log_addr;
    page_num = page;
    frame_num = frame;
    valid = fault;
}

// overload page entry constructor for lru 
PageEntry::PageEntry(int entry_log_addr, int page, int frame, bool fault, int lru_ind)
{
    log_addr = entry_log_addr;
    page_num = page;
    frame_num = frame;
    valid = fault;
    lru_index = lru_ind;
}

// page table default constructor
PageTable::PageTable()
{ 
    page_size = 0;
    mem_size = 0;
    frame_num_count = 0;
    ref_count = 0;
    fault_count = 0;
    replace_count = 0;
    fifo_n_lru_count = 0;
    lru_line = 0;
}

// create table
void PageTable::createTable(int table_size)
{
    // fill table with empty pages
    for (int i = 0; i < table_size; ++i)
    {
        PageEntry emptyPage;
        table.push_back(emptyPage);
    }
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

// check for LRU page and return its index 
int PageTable::checkLRU()
{
    int index = fifo_n_lru_count;
    int last_index = lru_line;
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].lru_index < last_index)
        {
            index = i;
            last_index = table[i].lru_index;
        }
    }
    return index;
}
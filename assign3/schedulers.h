#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

// add a task to the list 
void add(char *name, int priority, int burst);

// invoke the scheduler
void schedule();

// invoke RR scheduler
void scheduleRR(char *argQuantum);

void addPrint(char *name, int turnaround, int waiting);
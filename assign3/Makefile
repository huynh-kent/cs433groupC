###################################
# OS COURSE - CS 433 example
# 
###################################
CC = g++			# use g++ for compiling c++ code or gcc for c code
CFLAGS = -g -Wall 		# -std=c++11 compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
LIB = -lm			# linked libraries	
LDFLAGS = -L.			# link flags
PROG = sjf fcfs rr priority priority_rr		# target executables (output)
SRCS = driver.cpp schedule_fcfs.cpp schedule_rr.cpp schedule_sjf.cpp schedule_priority.cpp schedule_priority_rr.cpp  \
     list.cpp CPU.cpp # .c or .cpp source files.
OBJ = $(SRCS:.cpp=.o) 	# object files for the target. Add more to this and next lines if there are more than one source files.

all : $(PROG) depend

fcfs: driver.o schedule_fcfs.o list.o CPU.o
	$(CC) -o fcfs driver.o schedule_fcfs.o list.o CPU.o $(LDFLAGS) $(LIB)

rr: driver.o schedule_rr.o list.o CPU.o
	$(CC) -o rr driver.o schedule_rr.o list.o CPU.o $(LDFLAGS) $(LIB)

sjf: driver.o schedule_sjf.o list.o CPU.o
	$(CC) -o sjf driver.o schedule_sjf.o list.o CPU.o $(LDFLAGS) $(LIB)

priority: driver.o schedule_priority.o list.o CPU.o
	$(CC) -o priority driver.o schedule_priority.o list.o CPU.o $(LDFLAGS) $(LIB)

priority_rr: driver.o schedule_priority_rr.o list.o CPU.o
	$(CC) -o priority_rr driver.o schedule_priority_rr.o list.o CPU.o $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@
	
depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

include .depend

# cleanup
clean:
	/bin/rm -f *.o $(PROG) .depend

# DO NOT DELETE

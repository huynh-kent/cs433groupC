/*
Implement Project 4 "The Producer-Consumer Problem" in chapter 7 of the textbook (P43 to P45 of eBook)

Using the Pthreads API
Should allow creating multiple producer and consumer threads
Three parameters are passed on the command line
    1. How long the main thread sleep before terminating (in seconds)
    2. The number of producer threads
    3. The number of consumer threads

Keep track and print out the content of the shared buffer during the execution of the threads when an item is added or consumed

For example, print message like
    'item 2 inserted by a producer. the current content of the buffer is [4,5,2].'

Items should be removed in their order of being added, FIRST IN FIRST OUT.
Make Sure the program works correctly
Include <pthread.h> header file and link the pthread library using "-lpthread"

The producer and consumer threads should sleep for some random time but shouldnt probably sleep for more than one second.
You may use the 'usleep()' function like 'usleep(rand()%10000000);' where usleep() functions sleeps for some number of microseconds.

EXTRA CREDIT:
You may gain extra credits for this assignment by doing more work beyond the requirements,
for example implementing the bounded buffer as a monitor using mutex and condition variables or other things interesting or creative.
The extra credit depends on the amount of extra work you do but will be no more than 10 points.
Please clearly describe the additional work you do in the report if you want to claim extra credits.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// import pthreads & semaphores
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"
#include <time.h>
#include <iostream>

using namespace std;

// create locks
sem_t empty;
sem_t full;
pthread_mutex_t mutexlock;

// buffer variables
int in, out, buffer_count;
buffer_item buffer[BUFFER_SIZE];

// initialize buffer
void init_buffer()
{
    pthread_mutex_init(&mutexlock, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    in = out = buffer_count = 0;
}

// destroy buffer
void destroy_buffer()
{
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutexlock);
}

// insert item
int insert_item(buffer_item item)
{
    // insert item into buffer
    if (buffer_count != BUFFER_SIZE)
    {   // return 0 if successful
        buffer[in] = item;
        in = (in+1)%(BUFFER_SIZE+1);
        buffer_count++;

        return 0;  
    }
    else // otherwise, return -1 indicating an error condition
    {
        printf("Buffer is FULL\n");
        return -1;
    }
    // exit critical section
}

// remove item
int remove_item(buffer_item *item)
{
    // remove an object from buffer
    if (buffer_count!=0)
    {   // placing it in item, return 0 if successful
        *item = buffer[out];
        out = (out+1)%(BUFFER_SIZE+1);
        buffer_count--;
        return 0;
    }
    else // otherwise, return -1 indicating an error condition
    {
        printf("Buffer is EMPTY\n");

        return -1;
    }
}

// producer thread
void *producer(void *param) {
    buffer_item item;
    int not_success = 0;
    while (1)
    {
        // sleep for a random period of time
        unsigned int seed = time(NULL);
        usleep(rand_r(&seed)%10000000);
        item = (rand()%1000)+1; // item #1-1000
        sem_wait(&empty);
        pthread_mutex_lock(&mutexlock);

        // enter critical section
        // insert item
        not_success = insert_item(item);
        pthread_mutex_unlock(&mutexlock);
        sem_post(&full);
        // exit critical section

        if (not_success) fprintf(stderr, "Producer - report error condition\n");
        else printf("Producer produced item #%d - Current Buffer Content - %d out of %d - Item #%d\n", item, buffer_count, BUFFER_SIZE, item);
    }
}

// consumer thread
void *consumer(void *param) {
    buffer_item item;
    int not_success = 0;
    while (1) 
    {
        // sleep for a random period of time
        unsigned int seed = time(NULL)/rand();
        usleep(rand_r(&seed)%10000000);
        sem_wait(&full);
        pthread_mutex_lock(&mutexlock);

        // enter critical section
        // remove item
        not_success = remove_item(&item);
        pthread_mutex_unlock(&mutexlock);
        sem_post(&empty);
        // exit critical section

        if (not_success) fprintf(stderr, "Consumer - report error condition\n");
        else printf("Consumer consumed item #%d - Current Buffer Content - %d out of %d - Item #%d\n", item, buffer_count, BUFFER_SIZE, item);
    }

}

int main(int argc, char *argv[]) {
    std::cout << "CS 433 Programming assignment 4" << std::endl;
    std::cout << "Authors: Kent Huynh, Daniel Martinez, and Raymond Quach" << std::endl;
    std::cout << "Date: 04/26/2022" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description : Solving the Producer-Consumer Problem" << std::endl;
    std::cout << "Creates Producer and Consumer threads that have a shared buffer" << std::endl;
    std::cout << "The buffer has a default size of 5 (changeable in the buffer.h file)" << std::endl;
    std::cout << "The program takes arguments of #ofSeconds, #ofProducers, #ofConsumers" << std::endl;
    std::cout << "#ofSeconds = How long main program waits before exiting" << std::endl;
    std::cout << "#ofProducers = How many producers are created" << std::endl;
    std::cout << "#ofConsumers = How many consumers are created" << std::endl;
    std::cout << "Example: './prog4 100 2 2' have 2 producers and 2 consumers run for 100 seconds" << std::endl;
    std::cout << "=================================" << std::endl;
/*
    1. get commmand line arguments argv[1], argv[2], argv[3]
    2. init buffer
    3. create producer thread(s)
    4. create consumer thread(s)
    5. sleep
    6. exit
*/
    // 1. get command line arguments argv[1,2,3]
    if (argc != 4)
    {
        fprintf(stderr, "Invalid Argument Format, Try Again.\n");
        return -1;
    }

    // parse args [1]-sleep time [2]-num of producers [3]-num of consumers
    int args[4];
    for (int i=1; i < 3; ++i)
    {
        args[i] = atoi(argv[i]);
    }

    // checks arguments
    for (int i=1; i<4; i++)
    {
        if (atoi(argv[i])<0)
        {
            fprintf(stderr, "Invalid Argument, Positive Integers Only.\n");
            return -1;
        }
    }

    // 2. init buffer
    init_buffer();

    // 3. create producer threads
    pthread_t producers[args[2]];
    for (int i=0; i<args[2]; i++)
    {
        pthread_create(&producers[i], NULL, producer, NULL);
    }
    // 4. create consumer threads
    pthread_t consumers[args[3]];
    for (int j=0; j<args[3]; j++)
    {
        pthread_create(&consumers[j], NULL, consumer, NULL);
    }
    // 5. sleep
    sleep(args[1]);
    // 6. exit
    destroy_buffer();
    return 0;
}
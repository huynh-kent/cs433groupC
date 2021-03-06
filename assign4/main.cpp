#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// import pthreads & semaphores
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

// for better randomness
#include <time.h>

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

// print buffer content
void print_buffer()
{
    for (int i=0; i<buffer_count; ++i)
    {
        if (buffer_count == 1 || i == buffer_count-1) printf("%d", buffer[(out+i)%(BUFFER_SIZE)]);
        else printf("%d, ", buffer[(out+i)%(BUFFER_SIZE)]);
    }
}

// insert item
int insert_item(buffer_item item)
{
    // insert item into buffer
    if (buffer_count != BUFFER_SIZE)
    {   // return 0 if successful
        buffer[in] = item;
        in = (in+1)%(BUFFER_SIZE);
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
        out = (out+1)%(BUFFER_SIZE);
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
    while (1)
    {
        // sleep for a random period of time
        unsigned int seed = time(NULL)%100;
        usleep((rand_r(&seed)%1000000)+500000); // sleep for at least .5 seconds
        //usleep(rand()%1000000);

        item = (rand()%1000)+1; // item #1-1000

        sem_wait(&empty);
        pthread_mutex_lock(&mutexlock);
        // enter critical section
        // insert item
        if (insert_item(item)) fprintf(stderr, "Producer - Failed to insert item\n");
        else {
            printf("Producer produced item #%d - Current Buffer Content - [", item);
            print_buffer();
            printf("]\n\n");
        } 
        pthread_mutex_unlock(&mutexlock);
        sem_post(&full);
        // exit critical section
    }
}

// consumer thread
void *consumer(void *param) {
    buffer_item item;
    while (1) 
    {
        // sleep for a random period of time
        unsigned int seed = time(NULL)%78;
        usleep((rand_r(&seed)%1000000)+500000); // sleep for at least .5 seconds

        sem_wait(&full);
        pthread_mutex_lock(&mutexlock);
        // enter critical section
        // remove item
        if (remove_item(&item)) fprintf(stderr, "Consumer - Failed to remove item\n");
        else {
            printf("Consumer consumed item #%d - Current Buffer Content - [", item);
            print_buffer();
            printf("]\n\n");
        }
        pthread_mutex_unlock(&mutexlock);
        sem_post(&empty);
        // exit critical section
    }

}

int main(int argc, char *argv[]) {
    printf("CS 433 Programming assignment 4\n");
    printf("Authors: Kent Huynh, Daniel Martinez, and Raymond Quach\n");
    printf("Date: 04/26/2022\n");
    printf("Course: CS433 (Operating Systems)\n");
    printf("Description : Solving the Producer-Consumer Problem\n");
    printf("Creates Producer and Consumer threads that have a shared buffer\n");
    printf("Solve Producer-Consumer Problem using Sempahores & Mutex Locks\n");
    printf("The buffer has a default size of 5 (changeable in the buffer.h file)\n");
    printf("The program takes arguments of #ofSeconds, #ofProducers, #ofConsumers\n");
    printf("#ofSeconds = How long main program waits before exiting\n");
    printf("#ofProducers = How many producers are created\n");
    printf("#ofConsumers = How many consumers are created\n");
    printf("Example: './prog4 100 2 2' have 2 producers and 2 consumers run for 100 seconds\n");
    printf("=================================\n");
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
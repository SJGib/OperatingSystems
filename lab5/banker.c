/*
 * Banker's Algorithm for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <omp.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3


// Put global environment variables here
// Available amount of each resource
int available[NUM_RESOURCES];

// Maximum demand of each customer
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];


// Define functions declared in banker.h here
// bool request_res(int n_customer, int request[])
// {
//      ...
// }

//Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{
    for (int i=0; i<NUM_RESOURCES; i++) {
        if (release[i] > allocation[n_customer][i]) {
            return 0;
        }
    }

    for (int j=0; j<NUM_RESOURCES; j++) {
        available[j] = available[j] + allocation[n_customer][j];
        allocation[n_customer][j] = 0;
    }

    return 1;    
}    


int main(int argc, char *argv[])
{
    // Read in arguments from CLI, NUM_RESOURCES is the number of arguments

    // If the number of CLI arguments are the same as resources (subtract one since the ./banker counts as 1)
    // Then insert the CLI arguments into available
    if((argc-1) == NUM_RESOURCES){
        // Start the for loop at 1 so that ./banker is not inserted
        for(int i = 1; i < argc; i++){
            // Allocate the available resources

            // Insert in i-1 so that the 0th element is filled and it doesn't exceed the NUM_RESOURCES
            // atoi casts the string argument to an integer
            available[i-1] = atoi(argv[i]);
        }
    }

    #ifdef _OPENMP
    // Initialize the openMP threads
    omp_set_num_threads(NUM_CUSTOMERS);

    // Run the threads and continually loop



    #endif

    // The threads will request and then release random numbers of resources

    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}
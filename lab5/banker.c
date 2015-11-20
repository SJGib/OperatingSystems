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
#include <time.h>
#include "banker.h"

// Put any other macros or constants here using #define
// May be any values >= 0
#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3
#define MAX_RESOURCES 100
#define NUM_OPTIONS 4

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
bool request_res(int n_customer, int request[]){
    // check each resource
    for(int i=0;i<NUM_RESOURCES;i++){
        // check if the request would be safe
        if(request[i]<available[i] || 
            (request[i]+allocation[n_customer][i])>maximum[n_customer][i] ||
            need[n_customer][i]>available[i]){
            // returns 0 if any of the values for requested resources would be unsafe
            return 0;
        }
    }
    for(int i=0; i<NUM_RESOURCES; i++){
        // remove from available resources
        available[i]-=request[i];
        // allocate to customer
        allocation[n_customer][i]+=request[i];
        // remove from need
        need[n_customer][i]-=request[i];
    }
    return 1;
}

//Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{
    for (int i=0; i<NUM_RESOURCES; i++) {
        if (release[i] > allocation[n_customer][i]) {
            return 0;
        }
    }

    for (int i=0; i<NUM_RESOURCES; i++) {
        available[i] += release[i];
        allocation[n_customer][i] -= release[i];
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
    #endif

    // Run the threads and continually loop
    int resources[3];
    #pragma omp parallel
    {
        while(1){
            // Randomly select a customer from 0 to 4
            srand(time(NULL));
            int cust = rand() % NUM_CUSTOMERS;

            // Randomly selected a resource from 0-100
            srand(time(NULL));
            int req1 = rand() % (MAX_RESOURCES+1);
            // Randomly selected a resource from 0-100
            srand(time(NULL));
            int req2 = rand() % (MAX_RESOURCES+1);
            // Randomly selected a resource from 0-100
            srand(time(NULL));
            int req3 = rand() % (MAX_RESOURCES+1);

            resources[0] = req1;
            resources[1] = req2;
            resources[2] = req3;

            // Randomly select if request, release or both(in which order) are called (0, 1, 2, 3)
            srand(time(NULL));
            int funCall = rand() % NUM_OPTIONS;

            // Based on the random number, call request or release
            #pragma omp critical
            {
                if(funCall == 0){
                    request_res(cust, resources);
                } 
                else if(funCall == 1){
                    release_res(cust, resources);
                } 
                else if(funCall == 2){
                    request_res(cust, resources);
                    release_res(cust, resources);
                } else{
                    release_res(cust, resources);
                    request_res(cust, resources);
                }
            }
        }
    }
    
    // The threads will request and then release random numbers of resources

    // If your program hangs you may have a deadlock, otherwise you *may* have
    // implemented the banker's algorithm correctly
    
    // If you are having issues try and limit the number of threads (NUM_CUSTOMERS)
    // to just 2 and focus on getting the multithreading working for just two threads

    return EXIT_SUCCESS;
}
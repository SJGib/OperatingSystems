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
#define MAX_RESOURCES 5
#define NUM_OPTIONS 4

// Put global environment variables here
// Available amount of each resource
int available[NUM_RESOURCES];

// Amount currently allocated to each customer
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];

// Remaining need of each customer
int need[NUM_CUSTOMERS][NUM_RESOURCES];

bool unavail[NUM_CUSTOMERS] = {false};

// finished customers
bool finish[NUM_CUSTOMERS] = {false};

bool safe(int n_customer, int request[]){
	for(int i=0; i<NUM_RESOURCES; i++){
		if(need[n_customer][i]<request[i]){
			return 0;
		}
		if(finish[n_customer] || need[n_customer][i]>available[i] ||
			(request[i]+allocation[n_customer][i])>MAX_RESOURCES){
			return 0;
		}
		if(request[i]>available[i]){
			unavail[n_customer] = true;
			return 0;
		}
		unavail[n_customer] = false;
	}
	return 1;
}

// Define functions declared in banker.h here
bool request_res(int n_customer, int request[]) {
    // check if the request would be safe
    if(!safe(n_customer, request)){
    	return 0;
    }
    for(int i=0; i<NUM_RESOURCES; i++){
        // remove from available resources
        available[i]-=request[i];
        // allocate to customer
        allocation[n_customer][i]+=request[i];
        // remove from need
        need[n_customer][i]-=request[i];
    }
    if(need[n_customer][0]<=0 && need[n_customer][1]<=0 &&
    	need[n_customer][2]<=0){
    	finish[n_customer]=true;
    }
    return 1;
}

//Release resources, returns true if successful
bool release_res(int n_customer, int release[])
{
    // Checks each resource.
    for (int i=0; i<NUM_RESOURCES; i++) {
        // Checks if the release would be safe.
        if (release[i] > allocation[n_customer][i]) {
            // Returns 0 if any of the releases would be unsafe.
            return 0;
        }
    }

    for (int i=0; i<NUM_RESOURCES; i++) {
        // Releases the resources back to available resources.
        available[i] += release[i];
        // Releases from allocation resources.
        allocation[n_customer][i] -= release[i];
    }
    // Returns 1 if releasing the resources would be safe.
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
            if(available[i-1]<MAX_RESOURCES){
            	printf("Too few resources to complete tasks.\n");
            	return 0;
            }
        }
    } else {
        printf("Invalid number of resource types.\n");
        return 0;
    }

    #ifdef _OPENMP
    // Initialize the openMP threads
    omp_set_num_threads(NUM_CUSTOMERS);
    #endif

    srand(time(NULL));

    // Run the threads and continually loop
    int resources[3];
    #pragma omp parallel
    {
        // thread number of current thread is the customer number
        int cust = omp_get_thread_num();
        need[cust][0] = rand() % (MAX_RESOURCES);
        need[cust][1] = rand() % (MAX_RESOURCES);
        need[cust][2] = rand() % (MAX_RESOURCES);

        while(1){
            bool done = 1;
            for(int j=0; j<NUM_RESOURCES; j++){
                // check if it no longer needs any resources
                if(need[cust][j]>0){
                    done = 0;
                }
            }
            if(done){
                // ends loop of current customer
                printf("All customers finished.\n");
                break;
            }

            if(!unavail[cust]){
	            // Randomly selected a resource from 0-100
	            int req1 = rand() % (MAX_RESOURCES+1);
	            // Randomly selected a resource from 0-100
	            int req2 = rand() % (MAX_RESOURCES+1);
	            // Randomly selected a resource from 0-100
	            int req3 = rand() % (MAX_RESOURCES+1);

	            resources[0] = req1;
	            resources[1] = req2;
	            resources[2] = req3;
	        }

            // Randomly select if request, release or both(in which order) are called (0, 1, 2, 3)
            int funCall = rand() % NUM_OPTIONS;

            // Based on the random number, call request or release
            #pragma omp critical
            {
             #ifdef _OPENMP
                if(funCall == 0){
                    printf("Request. Thread: %d, resource 1: %d, resource 2: %d, resource 3: %d, safe/accepted: %d\n", 
                        cust, resources[0], resources[1], resources[2],request_res(cust, resources));
                } 
                else if(funCall == 1){
                    printf("Release. Thread: %d, resource 1: %d, resource 2: %d, resource 3: %d, safe/accepted: %d\n", 
                        cust, resources[0], resources[1], resources[2],release_res(cust, resources));
                } 
                else if(funCall == 2){
                    printf("Request. Thread: %d, resource 1: %d, resource 2: %d, resource 3: %d, safe/accepted: %d\n", 
                        cust, resources[0], resources[1], resources[2],request_res(cust, resources));
                    printf("Release. Thread: %d, resource 1: %d, resource 2: %d, resource 3: %d, safe/accepted: %d\n", 
                        cust, resources[0], resources[1], resources[2],release_res(cust, resources));
                } else{
                    printf("Release. Thread: %d, resource 1: %d, resource 2: %d, resource 3: %d, safe/accepted: %d\n", 
                        cust, resources[0], resources[1], resources[2],release_res(cust, resources));
                    printf("Request. Thread: %d, resource 1: %d, resource 2: %d, resource 3: %d, safe/accepted: %d\n", 
                        cust, resources[0], resources[1], resources[2],request_res(cust, resources));
                }
             #endif
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
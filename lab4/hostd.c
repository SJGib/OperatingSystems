/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */

#define _GNU_SOURCE

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here
int time = 0;

// Define functions declared in hostd.h here

int main(void)
{
    // dispatch queue head and tail
    node_t *dispatch_head = NULL;
    node_t *dispatch_tail = NULL;
    // queue heads and tails
    node_t *heads[4] = {NULL};
    node_t *tails[4] = {NULL};

    // Load the dispatchlist
    // Add each process structure instance to the job dispatch list queue
    load(&dispatch_tail, &dispatch_head);
    
    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues
    proc process;
    int priority;
    while(dispatch_head != NULL){
    	// retrieve process
    	process = pop(&dispatch_head, &dispatch_tail);
    	// retrieve priority of the process
    	priority = process.details[1];
    	// push process onto queue with matching priority
    	push(&(tails[priority]), process);
    	// queue with 1 node
    	if(heads[priority]==NULL){
    		heads[priority] = tails[priority];
    	}
    }

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}

void load(node_t **tail, node_t **head){
	size_t str_length = 256;
	// open file
    FILE *fp = fopen("dispatchlist","r");
    if(fp==NULL){
        perror("Could not open file.\n");
        exit(0);
    }

    // allocate memory for line
    char *line = calloc(str_length+1, sizeof(char));
    // loop through lines in file
    while(getline(&line,&str_length,fp) != -1){
		// push process onto queue
        push(tail, load_dispatch(line));

        // from empty queue to queue with only one element
        if(*head==NULL){
            *head = *tail;
        }
    }

    // free memory used by line
    free(line);

    fclose(fp);
}
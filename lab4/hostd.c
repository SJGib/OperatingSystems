/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
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
#define 

// Put global environment variables here
int time = 0;

// Define functions declared in hostd.h here

int main(int argc, char *argv[])
{
    // dispatch queue head and tail
    node_t *dispatch_head = NULL;
    node_t *dispatch_tail = NULL;
    // queue heads and tails
    node_t *heads[4] = {NULL};
    node_t *tails[4] = {NULL};

    // ==================== YOUR CODE HERE ==================== //
    
    // Load the dispatchlist
    /*load(dispatch_tail, dispatch_head);*/
    
    // Add each process structure instance to the job dispatch list queue

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}

void load(node_t *tail, node_t *head){
    /*FILE *fp = fopen("dispatchlist","r");
    if(fp==NULL){
        perror("Could not open file.\n");
        exit(0);
    }

    char *line = calloc(sizeof(char)*256);
    while(getline(line,256,fp) != -1){
        push(tail, load_dispatch(line));

        if(head==NULL){
            head = tail;
        }
    }

    fclose(fp);*/
}
/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// The amount of available memory
#define MEMORY 1024

// Resources structure containing integers for each resource constraint and an
// array of 1024 for the memory
typedef struct {
	int printer[2];
	int scanner;
	int modem;
	int cdDrive[2];
	int has_printer[2];
	int has_scanner;
	int has_modem;
	int has_cdDrive[2];
	int memory[MEMORY];
} resources;

// Processes structure containing all of the process details parsed from the 
// input file, should also include the memory address (an index) which indicates
// where in the resources memory array its memory was allocated
typedef struct {
	int pid;
	int details[8];
	int addressIndex;
} proc;

// Include your relevant functions declarations here they must start with the 
//extern keyword such as in the following examples:

// Function to allocate a contiguous chunk of memory in your resources structure
// memory array, always make sure you leave the last 64 values (64 MB) free, should
// return the index where the memory was allocated at
extern int alloc_mem(resources *res, int size);

// Function to free the allocated contiguous chunk of memory in your resources
// structure memory array, should take the resource struct, start index, and 
// size (amount of memory allocated) as arguments
extern void free_mem(resources *res, int index, int size);

/**
 * Function to allocate required resources for the process
 */
extern bool alloc_res(resources *res, proc *process);

/**
 * Function to free resources allocated for the process
 */
extern void free_res(resources *res, proc process);

// Function to parse the file and initialize each process structure and add
// it to your job dispatch list queue (linked list)
extern proc load_dispatch(char *process_info);


#endif /* UTILITY_H_ */
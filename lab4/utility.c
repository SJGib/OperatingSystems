/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

#define MEMORY 1024

// Define your utility functions here, you will likely need to add more...

int alloc_mem(resources res, int size)
{
	int startIndex = -1;
	int endIndex = -1;
	int currCounter = 0;

	for (int i=0; i<MEMORY-64; i++) {

		// Issues the start index.
		if (currCounter == 0) {
			startIndex = i;
		}

		if (res.memory[i] != 0) { // Increases counter if empty.
			currCounter++;
		} else { // Restarts counter if not empty.
			currCounter = 0;
		}

		// Marks end index when enough memory to allocate.
		if (currCounter == size) {
			endIndex = i;
		}
	}

	// Sets all memory spots to 1 if there is enough memory spots.
	if (endIndex != -1) {
		for (int j=startIndex; j<endIndex+1; j++) {
			res.memory[j] = 1;
		}
	}

	return startIndex;
}

void free_mem(resources res, int index, int size)
{
	// Sets all memory spots to open.
	for (int i=index; i<index+size; i++) {
		res.memory[i] = 0;
	}
}

proc load_dispatch(char *process_info)
{
	proc loadedProc;
	int currCounter = 0;
	char *processInfoCopy = process_info;
	char s[3] = ", ";
	char *token;
   	
   	// Get the first token.
   	token = strtok(processInfoCopy, s);
   	
   	// Walk through other tokens.
   	while( token != NULL )
   	{
      	loadedProc.details[currCounter] = atoi(token);

   		currCounter++;
    	token = strtok(NULL, s);
   	}

   	// Need to change this, need to figure out the starting index.
   	// 0 used for now.
   	loadedProc.addressIndex = 0;

	return loadedProc;
}
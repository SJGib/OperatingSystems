/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include "utility.h"

#define MEMORY 1024

// Define your utility functions here, you will likely need to add more...

int alloc_mem(resources *res, int size)
{
	int startIndex = -1;
	int endIndex = -1;
	int currCounter = 0;

	for (int i=0; i<MEMORY-64; i++) {

		// Issues the start index.
		if (currCounter == 0) {
			startIndex = i;
		}

		if (res->memory[i] != 0) { // Increases counter if empty.
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
			res->memory[j] = 1;
		}
	}

	return startIndex;
}

void free_mem(resources *res, int index, int size)
{
	// Sets all memory spots to open.
	for (int i=index; i<index+size; i++) {
		res->memory[i] = 0;
	}
}

bool alloc_res(resources *res, proc *process){
	if(res->has_printer[0]==process->pid || res->has_printer[1]==process->pid ||
		res->has_scanner==process->pid || res->has_modem==process->pid ||
		res->has_cdDrive[0]==process->pid || res->has_cdDrive[1]==process->pid){
		return 1;
	}
	if((process->details[4] + res->printer[0] + res->printer[1])>2){
		return 0;
	}
	if((process->details[5] + res->scanner)>1){
		return 0;
	}
	if((process->details[6] + res->modem)>1){
		return 0;
	}
	if((process->details[7] + res->cdDrive[0] + res->cdDrive[1])>2){
		return 0;
	}
	if((process->addressIndex = alloc_mem(res, process->details[3]))==(-1)){
		return 0;
	}
	for(int i=0; i<2; i++){
		if(res->printer[i]!=1){
			res->printer[i] = 1;
			res->has_printer[i] = process->pid;
			if(i==0 && process->details[4]==1){
				break;
			}
		}
	}
	if(process->details[5]>0){
		res->scanner = 1;
		res->has_scanner = process->pid;
	}
	if(process->details[6]>0){
		res->modem = 1;
		res->has_modem = process->pid;
	}
	for(int i=0; i<2; i++){
		if(res->cdDrive[i]!=1){
			res->cdDrive[i] = 1;
			res->has_cdDrive[i] = process->pid;
			if(i==0 && process->details[7]==1){
				break;
			}
		}
	}
for(int j=0;j<MEMORY;j++){
   	printf("%d",res->memory[j]);
}
printf("\n");
	return 1;
}

void free_res(resources *res, proc process){
	if(res->has_printer[0]==process.pid){
		res->printer[0] = 0;
		res->has_printer[0] = -1;
	}
	if(res->has_printer[1]==process.pid){
		res->printer[1] = 0;
		res->has_printer[1] = -1;
	}
	if(res->has_scanner==process.pid){
		res->scanner = 0;
		res->has_scanner = -1;
	}
	if(res->has_modem==process.pid){
		res->modem = 0;
		res->has_modem = -1;
	}
	if(res->has_cdDrive[0]==process.pid){
		res->cdDrive[0] = 0;
		res->has_cdDrive[0] = -1;
	}
	if(res->has_cdDrive[1]==process.pid){
		res->cdDrive[1] = 0;
		res->has_cdDrive[1] = -1;
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
   	loadedProc.addressIndex = -1;
   	loadedProc.waiting = 1;

	return loadedProc;
}
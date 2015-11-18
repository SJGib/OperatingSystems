/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#define _GNU_SOURCE

#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here
int time = 0;

// Define functions declared in hostd.h here

int main(void)
{
	resources *res = (resources *) calloc(1, sizeof(resources));
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
    	push(&(heads[priority]), &(tails[priority]), process);
    }

    int time = 0;
    // pid of first process for which there are not enough available resources
    int res_taken_pid = -1;
    // Repeat until all processes have been executed, all queues are empty
    while(heads[0]!=NULL || heads[1]!=NULL
    	|| heads[2]!=NULL || heads[3]!=NULL){
    	for(priority=0; priority<4; priority++){
    		while(heads[priority]!=NULL && 
    			res_taken_pid!=heads[priority]->process.pid){
    			process = pop(&(heads[priority]), &(tails[priority]));
    			if(process.details[0]<=time){
	    			// Allocate the resources for each process before it's executed
	    			if(alloc_res(res, &process)){
	    				pid_t pid = -1;
	    				if(!process.waiting){
	    					kill(process.pid, SIGCONT);
	    					waitpid(process.pid,0,0);
	    					pid = process.pid;
	    				} else {
	    					process.waiting = 0;
	    					// Execute the process binary using fork and exec
	    					pid = fork() + 2;
	    					if(pid == 1){
	    						perror("fork");
								exit(1);
	    					} else if(pid == 2){
	    						// run process
	    						system("./process");
	    						exit(0);
	    					}
	    				}
	    				if(pid>2){
	    					// wait 1 second or until finished
	    					if(priority>0){
	    						sleep(1);
	    						process.details[2]--;
	    						time++;
	    						if(process.details[2]>0){
		    						// Perform the appropriate `nal handling
		    						kill(pid, SIGTSTP);
		    					} else {
		    						kill(pid, SIGINT);
		    					}
	    						waitpid(pid,0,0);
	    						// set process pid + res->has_x to pid+2
	    						if(process.pid!=pid){
	    							if(res->has_printer[0]==process.pid){
	    								res->has_printer[0]=pid;
	    							}
	    							if(res->has_printer[1]==process.pid){
	    								res->has_printer[1]=pid;
	    							}
	    							if(res->has_scanner==process.pid){
	    								res->has_scanner=pid;
	    							}
	    							if(res->has_modem==process.pid){
	    								res->has_modem=pid;
	    							}
	    							if(res->has_cdDrive[0]==process.pid){
	    								res->has_cdDrive[0]=pid;
	    							}
	    							if(res->has_cdDrive[1]==process.pid){
	    								res->has_cdDrive[1]=pid;
	    							}
	    							process.pid = pid;
	    						}
	    					} else {
	    						sleep(process.details[2]);
	    						time+= process.details[2];
	    						process.details[2] = 0;
	    						// Perform the appropriate signal handling
	    						kill(pid, SIGINT);
	    						waitpid(pid,0,0);
	    					}
	    				}
	    				if(process.details[2]>0){
	    					// push to next highest priority queue
	    					if(priority<3){
		    					push(&(heads[priority+1]), &(tails[priority+1]), process);
	    					} else {
	    						push(&(heads[priority]), &(tails[priority]), process);
	    					}
	    				} else {
	    					// resource de-alloaction
	    					free_res(res, process);
	    					free_mem(res, process.addressIndex, process.details[3]);
	    				}
	    			} else {
	    				if(res_taken_pid<0){
		    				res_taken_pid = process.pid;
	    				}
	    				push(&(heads[priority]), &(tails[priority]), process);
	    			}
	    		} else {
	    			push(&(heads[priority]), &(tails[priority]), process);
	    			if(res_taken_pid<0){
	    				res_taken_pid = process.pid;
	    			}
	    		}
    		}
    		res_taken_pid = -1;
    	}
    } // End repeat

    free(res);
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
    int pid_count = 0;
    // loop through lines in file
    while(getline(&line,&str_length,fp) != -1){
		// push process onto queue
        push(head, tail, load_dispatch(line));
        (*tail)->process.pid = pid_count++;
    }

    // free memory used by line
    free(line);

    fclose(fp);
}
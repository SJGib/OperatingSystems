/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"

// Define your utility functions here, these will most likely be functions that you call
// in your myshell.c source file

void print(char *content){
	printf("%s", &content);

	free(content);
}

void cmd_cd(char *directory){
	int success;
	success = chdir(directory);
	if(success!=0){
		printf("Error: %s not found", directory);
	}
}

void cmd_clr(void){
	printf("\033[H\033[J"); //clears the screen
}

char* cmd_dir(){
	
}

char* cmd_environ(void){
	
	// Points to an array of char* (an array of strings) which points to an array of characters (string)
	// Each string is an environment variable for the current process
	// It comes from the unistd.h
	extern char **environ;
        
    // Initialize an index variable for the following loop
    int i = 0;

    // The last entry of the environ array is NULL so loop until NULL
    // Printing every environment variable as it iterates through the array
    while(environ[i] != NULL){
        printf("%s\n", environ[i]);
        i++;
    }
}

char* cmd_echo(){
	
}

char* cmd_help(void){
	
}

void cmd_pause(void){
	
}

void cmd_quit(void){
	
}
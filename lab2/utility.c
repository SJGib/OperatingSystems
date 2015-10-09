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

void cmd_dir(){

	// Makes a directory pointer which points to the current directory
	DIR *dir = opendir(".");

	// Pointer to the struct dirent
	// Included in the dirent.h
    struct dirent *contents;

    // if the directory you're in isn't null
    if(dir != NULL){
    	// Loop until the current directory has no files
    	// Prints every file name
        while((contents = readdir(dir)) != NULL){
            printf("%s\n", contents->d_name);
        }
        close(dir);
    }
}

void cmd_environ(void){		
	
	// Points to an array of char* (an array of strings) which points to an array of characters (string)
	// Each string is an environment variable for the current process
	// Included in the unistd.h
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

void cmd_echo(){
	
}

void cmd_help(void){
	
}

void cmd_pause(void){
	getchar();
}

void cmd_quit(void){
	
}
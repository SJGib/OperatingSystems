/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <Akira Aida - 100526064, Dennis Pacewicz - 100524231, Truyen Truong - 100516976, S Jack Gibson - 1005145564>
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

void cmd_cd(char *directory){
	int success;
	success = chdir(directory);// change directory, returns 0 for success, otherwise error
	if(success!=0){
		printf("Error: %s not found\n", directory);// print if error
	}

	// set PWD to new location
	char *current_dir[256] = { 0 };
    getcwd(current_dir, 256);
    setenv("PWD", current_dir, 1);
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
    	// Loop until the current directory has no more contents to list
    	// Prints every file name and directory name
        while((contents = readdir(dir)) != NULL){
            printf("%s\n", contents->d_name);
        }
        closedir(dir);
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

void cmd_echo(char *comment){
	// Prints out comment with a new line character after.
	printf("%s\n", comment);
}

void cmd_help(char help_dir[]){
	// Prints out the readme file.
	char line[256];

	FILE *fp;
	fp = fopen(help_dir, "r"); // Starts reading the readme.

	if(fp){
		while (fgets(line, 256, fp) != NULL) {
			printf("%s", line); // Prints out the readme line by line.
		}
		printf("\n");
	}
	fclose(fp);
}

void cmd_pause(void){
	
	do {
    	printf("Press ENTER to continue."); 
    } while (getchar() != '\n');
}

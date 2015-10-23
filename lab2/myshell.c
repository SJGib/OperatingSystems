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
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define HELP_LEN 1024

// Put global environment variables here
char help_dir[HELP_LEN];	// Stores the location of the readme.txt

// Define functions declared in myshell.h here
void locateReadMe(){
	// Puts the current working directory into the variable help_dir
    getcwd(help_dir, sizeof(help_dir));
    // Adds /readme.txt to the current working directory so the location of the readme is globally available
    strcat(help_dir, "/readme.txt");
}

void printCurrDir(){
	// Variable to store the current working directory
	char curr_dir[HELP_LEN];
	// Puts the current working directory into the variable curr_dir
    getcwd(curr_dir, sizeof(curr_dir));
    // Prints the current working directory
    printf("%s > ", curr_dir);
}

void tokenize(char *buffer, char *command, char *arg){
    char *newLine = strstr(buffer, "\n");
    if(newLine != NULL){
        *newLine = 0;
    }

    char *tokens = strtok(buffer, " ");
    strncpy(command, tokens, BUFFER_LEN);
    tokens = strtok(NULL, " ");

    while(tokens != NULL)
    {
        strcat(arg, tokens);
        tokens = strtok(NULL, " ");
        if(tokens!=NULL){
            strcat(arg, " ");
        }
    }

    //TODO: remove tab characters from tokenized strings
}

void execCommands(char *command, char *arg){

	if (strcmp(command, "cd") == 0){
		// Changes the directory
        cmd_cd(arg);
    } else if(strcmp(command, "clr") == 0){   
    	// Clears the shell
        cmd_clr();                                                                  
    } else if(strcmp(command, "dir") == 0){ 
    	// Lists all files and directories in the current working directory                                        
        cmd_dir();
    } else if(strcmp(command, "environ") == 0){                            
    	// Lists all the environment variables         
        cmd_environ();
    } else if(strcmp(command, "echo") == 0){  
    	// Echoes the inputted words after "echo"                               
        cmd_echo(arg); 
    } else if(strcmp(command, "help") == 0){     
    	// Prints the readme.txt to the shell                              
        cmd_help(help_dir);
    } else if(strcmp(command, "pause") == 0){   
    	// Pauses the shell                                    
        cmd_pause();
    } else{// Unsupported command
    	
        if(strstr("./",command)==NULL){
            for(int i=BUFFER_LEN-3; i>=0; i--){
                command[i+2] = command[i];
            }
            command[0] = '.';
            command[1] = '/';
        }

        if(access(command, F_OK)==0){
			pid_t pid = fork();;    
            printf("PID: %d \n",pid);

			if(pid==0){ // Child Process
                if(strcmp(arg, "&") == 0){
                    printf(" BACKGROUND\n");
                    freopen( "/dev/null", "r", stdin);
                    freopen( "/dev/null", "w", stdout);
                    freopen( "/dev/null", "w", stderr);
                }  
                char *parent[BUFFER_LEN] = { 0 };
                *parent = getenv("Shell");
                setenv("Parent", parent, 1);

				int status = system(command);

				if(status==-1){
					printf("Error running %s\n", command);
				}

				exit(0);
			} else {
                if (pid==-1){
				    perror("fork\n");
                } 
			}

        } else {
        	printf("%s, not found\n", command);
        }
    }
}

void batchfile(char* arg){

	// Created temporary strings for the file inputs
    char tempCommand[BUFFER_LEN] = { 0 };
    char tempArg[BUFFER_LEN] = { 0 };

    // Create variables for reading the file
   	FILE *fp;
   	char line[BUFFER_LEN];
    
   	// Open the file in read mode
    fp = fopen(arg, "r");

   	// If there is a file then read it and execute the commands
    if(fp == NULL){
    	printf("Error reading file.\n");
    } else{
    	while(fgets(line, BUFFER_LEN, fp)){
     		tokenize(line, tempCommand, tempArg);		//tokenize a line in the file
     		execCommands(tempCommand, tempArg);			//execute tokens in the line
    	}
        // Close the file if it isn't NULL
        fclose(fp);
    }
}

int main(int argc, char *argv[])
{
    char *origin[BUFFER_LEN] = { 0 };
    readlink("/proc/self/exe", origin, BUFFER_LEN);
    setenv("Shell", origin, 1);

    // Input buffer
    char buffer[BUFFER_LEN] = { 0 };

    // Locate the readme file at the start of the program before the directory has changed
    locateReadMe();

    // Parse the commands provided using argc and argv
    // If two arguments are given at the start. ie: ./myshell.exe <BATCHFILENAMEHERE>
    if(argc == 2){     
        batchfile(argv[1]);
    } else{
    	// Print the current directory to the console before user input
    	printCurrDir();
        //Perform an infinite loop getting command input from users
        while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
        {
            // Input commands
            char command[BUFFER_LEN] = { 0 };
            char arg[BUFFER_LEN] = { 0 };

            // Perform string tokenization to get the command and argument                  
        	tokenize(buffer, command, arg);

        	if (strcmp(command, "quit") == 0){
                return EXIT_SUCCESS;
            } else {
            // Check the command and execute the operations for each command
            	execCommands(command, arg);
        	}
        	// Print the current directory to the console before user input
        	printCurrDir();
        }
    }
    return EXIT_SUCCESS;
}
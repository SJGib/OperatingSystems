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
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here
       
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

void commands(char *command, char *arg){

	if (strcmp(command, "cd") == 0){// cd command -- change the current directory   
        cmd_cd(arg);
    } else if(strcmp(command, "clr") == 0){   
        cmd_clr();                                                                  
    } else if(strcmp(command, "dir") == 0){                                         
        cmd_dir();
    } else if(strcmp(command, "environ") == 0){                                     
        cmd_environ();
    } else if(strcmp(command, "echo") == 0){ //TODO: delimited by spaces, so it can only echo a single word...                                  
        cmd_echo(arg); 
    } else if(strcmp(command, "help") == 0){                                       
        cmd_help();
    } else if(strcmp(command, "pause") == 0){                                       
        cmd_pause();
    } else{// Unsupported command
    	//TODO: program invocation?
        if(strstr("./",command)==NULL){
            for(int i=BUFFER_LEN-3; i>=0; i--){
                command[i+2] = command[i];
            }
            command[0] = '.';
            command[1] = '/';
        }

        if(access(command, F_OK)==0){
			pid_t pid = fork();;

			if(pid==0){
                char *parent[BUFFER_LEN] = { 0 };
                *parent = getenv("Shell");
                setenv("Parent", parent, 1);

				int status = system(command);

				if(status==-1){
					printf("Error running %s\n", command);
				}

				exit(0);
			} else if (pid==-1){
				perror("fork\n");
			}
        } else {
        	printf("%s, not found\n", command);
        }
    }
}

void myshell(char* arg){

	// Created temporary strings for the file inputs
    char tempCommand[BUFFER_LEN] = { 0 };
    char tempArg[BUFFER_LEN] = { 0 };

    // Create variables for reading the file
   	FILE *fp;
   	char *line = NULL;
   	size_t len = 0;
   	char read;    
    
   	// Open the file in read mode
    fp = fopen(arg, "r");

   	// If there is a file then read it and execute the commands
    if(fp == NULL){
    	printf("Error reading file.\n");
    } else{
       	while((read = getline(&line, &len, fp)) != -1){  	          //getline is not supported in c however this works for some reason
                                                                        //should change later to get rid of the warning

     		tokenize(line, tempCommand, tempArg);		//tokenize "line"
     		commands(tempCommand, tempArg);				//execute tokens in the line
    	}
    }
    // Close the file
    fclose(fp);
}

int main(int argc, char *argv[])
{
    char *origin[BUFFER_LEN] = { 0 };
    readlink("/proc/self/exe", origin, 255);
    setenv("Shell", origin, 1);

    printf("%s\n", getenv("Shell"));

    // input buffer
    char buffer[BUFFER_LEN] = { 0 };

    // Parse the commands provided using argc and argv
    if(argc == 2){          //if two arguments are given at the start. ie: ./myshell.exe <BATCHFILENAMEHERE>
        myshell(argv[1]);
    } else{
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
            	commands(command, arg);
        	}
        }
    }
    return EXIT_SUCCESS;
}

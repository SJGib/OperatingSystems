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
    *newLine = 0;

    char *tokens = strtok(buffer, " ");
    strncpy(command, tokens, BUFFER_LEN);
    tokens="";
    while(tokens!=NULL){
        strncpy(arg, tokens, BUFFER_LEN);
        tokens = strtok(NULL, " ");
    }
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
    } else if(strcmp(command, "echo") == 0){                                       
        cmd_echo(arg); 
    } else if(strcmp(command, "help") == 0){                                       
        cmd_help();
    } else if(strcmp(command, "pause") == 0){                                       
        cmd_pause();
    } else if (strcmp(command, "quit") == 0){// quit command -- exit the shell
       cmd_quit();

       //THIS DOESN'T WORK

    } else{// Unsupported command
        fputs("Unsupported command, use help to display the manual\n", stderr);
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
       	while((read = getline(&line, &len, fp)) != -1){  	
     			
       		//printf("%s", line);							//prints each line in file

     		//tokenize(line, tempCommand, tempArg);		//tokenize line 	//SEG FAULTING HERE ON SECOND ITERATION - NOT SURE WHY		
     		//commands(tempCommand, tempArg);				//execute tokens
    	}
    	//printf("\n");
    }
    // Close the file
    fclose(fp);
}

int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };

    // Parse the commands provided using argc and argv

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Perform string tokenization to get the command and argument                  
    	tokenize(buffer, command, arg);

    	if(strcmp(command, "myshell") == 0){
    		myshell(arg);			//PRETTY SURE THIS IS THE WRONG IMPLEMENTATION OF THE COMMAND. CODE SHOULD BE USEABLE THOUGH
    	} else {
        // Check the command and execute the operations for each command
        	commands(command, arg);
    	}
    }
    return EXIT_SUCCESS;
}

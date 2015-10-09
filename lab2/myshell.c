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
        // Perform string tokenization to get the command and argument                  //JACK
        // strncpy(buffer, strtok(buffer, "\n"), BUFFER_LEN);
        // strncpy(command, strtok(buffer, " "), BUFFER_LEN);
        // for(char *tokens=strtok(NULL, " "; tokens; tokens=strtok(NULL, " "))){
        //     strncpy(arg, strtok(NULL, "\n"), BUFFER_LEN);
        // }
        
        // Check the command and execute the operations for each command
        if (strcmp(command, "cd") == 0){// cd command -- change the current directory   //JACK
            cmd_cd(&arg);
        } else if(strcmp(command, "clr") == 0){   
            cmd_clr();                                                                  //DENNIS
        } else if(strcmp(command, "dir") == 0){                                         //AKIRA
            cmd_dir();
        } else if(strcmp(command, "environ") == 0){                                     //AKIRA
            cmd_environ();
        } else if(strcmp(command, "echo") == 0){                                        //TRUYEN
            cmd_echo(buffer); // Need to replace buffer with thing to be echo'd.
        } else if(strcmp(command, "help") == 0){                                        //TRUYEN
            cmd_help();
        } else if(strcmp(command, "pause") == 0){                                       //DENNIS
            void cmd_pause();
        } else if (strcmp(command, "quit") == 0){// quit command -- exit the shell
            return EXIT_SUCCESS;
        } else{// Unsupported command
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
    }
    return EXIT_SUCCESS;
}

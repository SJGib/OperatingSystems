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

void cmd_prompt(void){
	
}

void print(char *content){
	printf("%s", &content);

	free(content);
}

void cmd_cd(){
	
}

void cmd_clr(void){
	
}

char* cmd_dir(){
	
}

char* cmd_environ(void){
	
}

char* cmd_echo(){
	
}

char* cmd_help(void){
	
}

void cmd_pause(void){
	
}

void cmd_quit(void){
	
}
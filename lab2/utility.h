/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#ifndef UTILITY_H_
#define UTILITY_H_
#include "utility.c"

// Include your relevant functions declarations here they must start with the 
// extern keyword such as in the following example:
// extern void display_help(void);

// print results of commands
// in: content to be printed
extern void print(char *content);

// change directory
// in: new directory
extern void cmd_cd(char *directory);

// clear shell
// no input/output
extern void cmd_clr(void);

// list directory contents
// in: directory to be listed
// out: contents of directory
extern void cmd_dir();

// list environment settings
// out: environment settings
extern void cmd_environ(void);

// display comment
// in: comment to be displayed
// out: comment to be displayed
extern void cmd_echo();

// display user manual
// out: user manual
extern void cmd_help(void);

// pause shell until "enter" is pressed
extern void cmd_pause(void);

// exit shell
extern void cmd_quit(void);

#endif /* UTILITY_H_ */
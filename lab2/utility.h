/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <Akira Aida - 100526064, Dennis Pacewicz - 100524231, Truyen Truong - 100516976, S Jack Gibson - 1005145564>
 * All rights reserved.
 * 
 */
#ifndef UTILITY_H_
#define UTILITY_H_
#include "utility.c"

// Include your relevant functions declarations here they must start with the 
// extern keyword such as in the following example:
// extern void display_help(void);

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
extern void cmd_echo(char *comment);

// display user manual
// out: user manual
extern void cmd_help(char help_dir[]);

// pause shell until "enter" is pressed
extern void cmd_pause(void);

#endif /* UTILITY_H_ */
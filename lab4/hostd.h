/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"

#ifndef HOSTD_H_
#define HOSTD_H_

// Include any relevant data structures here thay may be needed

// Include any relevant functions declarations here they must start with the 
// extern keyword such as in the following example:
// extern void print_process(proc process);

extern void load(node_t **tail, node_t **head);

#endif /* HOSTD_H_ */
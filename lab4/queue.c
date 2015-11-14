/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

void push(node_t **tail, proc process){
	// creates new node_t to push onto the queue
	node_t *new_node = (node_t *) malloc(sizeof(node_t));

	// assign the process to the new node
	new_node->process = process;
	// initiate the value of next to NULL
	new_node->next = NULL;

	if(*tail!=NULL){
		// add the new node to the queue
		(*tail)->next = new_node;
	}
	// assign tail to the new node
	*tail = new_node;
}

proc pop(node_t **head, node_t **tail){
	// create a new pointer to the node being popped from the queue
	proc process = (*head)->process;

	// assign head to the new head of the queue
	*head = (*head)->next;

	if(*head==NULL){
		*tail = NULL;
	}

	// return the popped node
	return process;
}

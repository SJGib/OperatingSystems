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

node_t *push(node_t *tail, proc process){
	// creates new node_t to push onto the queue
	node_t *new_node = (node_t *) malloc(sizeof(node_t));

	// assign the process to the new node
	new_node->process = process;
	// initiate the value of next to NULL
	new_node->next = NULL;

	// add the new node to the queue
	tail->next = new_node;
	// assign tail to the new node
	tail = new_node;

	// returns the new node
	return new_node;
}

node_t *pop(node_t *head){
	// create a new pointer to the node being popped from the queue
	node_t *popped_node = head;

	// assign head to the new head of the queue
	head = head->next;
	// assign the popped node's value of next to NULL
	popped_node->next = NULL;

	// return the popped node
	return popped_node;
}

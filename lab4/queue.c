/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

void push(node_t **head, node_t **tail, proc process){
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

    // from empty queue to queue with only one element
	if(*head==NULL){
    	*head = *tail;
    }
}

proc pop(node_t **head, node_t **tail){
	// create a new pointer to the process being popped from the queue
	proc process;
	if(*head==NULL){
		return process;
	}
	process = (*head)->process;

	// create pointer to popped node
	node_t *popped_node = *head;
	// assign head to the new head of the queue
	*head = (*head)->next;
	// free memory
	free(popped_node);

	if(*head==NULL){
		*tail = NULL;
	}

	// return the popped node
	return process;
}

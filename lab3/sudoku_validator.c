#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sudoku_validator.h"

#define SUDOKU_SIZE 9
#define NUM_THREADS 11

int sudBoard[SUDOKU_SIZE][SUDOKU_SIZE];

typedef struct
{
	int row;
	int column;
} parameters;

void init(){
	//read in file and put in sudBoard
}

void *checkSeg(void* arg){
	parameters* par = (parameters*) arg;




	return NULL;
}

int main(){

	//initialize sudoku board
	init();

	//create 11 threads
	pthread_t pth[NUM_THREADS];

	//create 11 structs, 1 for each thread
	parameters initials[NUM_THREADS];

	//segment checks
	for(int i = 0; i < SUDOKU_SIZE; i++){
		initials[i].row = (i%3)*3;
		initials[i].column = (i/3)*3;
	}

	//row check
	initials[10].row = 0;
	initials[10].column = 0;

	//col check
	initials[11].row = 0;
	initials[11].column = 0;

	//start segment checks
	for(int i = 0; i < 9; i++){
		pthread_create(&pth[i], 0, checkSeg, (void *)&initials[i]);
	}
}


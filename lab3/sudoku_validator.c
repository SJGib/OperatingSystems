#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "sudoku_validator.h"

#define SUDOKU_SIZE 9
#define NUM_THREADS 11
#define BUFFER_LEN 256

int puzzle[SUDOKU_SIZE][SUDOKU_SIZE];
int valid[NUM_THREADS] = {0};

typedef struct{
	int row;
	int column;
} parameters;

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
		initials[i].column = (i/3)*3;`
	}

	//row check
	initials[9].row = 0;
	initials[9].column = 0;

	//col check
	initials[10].row = 0;
	initials[10].column = 0;

	//start segment checks
	for(int i = 0; i < 9; i++){
		pthread_create(&pth[i], 0, check_all_grids, (void *)&initials[i]);
	}
	pthread_create(&pth[9], 0, check_all_rows, (void *)&initials[9]);
	pthread_create(&pth[10], 0, check_all_columns, (void *)&initials[10]);


	//join segments
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(pth[i], NULL);
	}
	
	// for(int i = 0; i < NUM_THREADS; i++){
	// 	printf("%d", valid[i]);
	// }
}

void init(){
	FILE *fp;
	fp = fopen("solved_puzzle.txt", "r");
	// row #
	int i = 0;

   	char line[BUFFER_LEN];
	int row[SUDOKU_SIZE] = { 0 };

    if(fp == NULL){
    	printf("Error reading file.\n");
    } else{
    	while(fgets(line, BUFFER_LEN, fp)){
    		// read line into 
    		tokenize(line, row);

    		// assign elements in row to their places in puzzle
    		for(int col = 0; col < SUDOKU_SIZE; col++){
    			puzzle[i][col] = row[col];
    		}
    		i++;
		}
        fclose(fp);
    }

}

void tokenize(char *line, int *array){
	// change end of line character for tokenizer
    char *newLine = strstr(line, "\n");
    if(newLine != NULL){
        *newLine = ' ';
    }

    // break line into strings separated by spaces
    char *tokens = strtok(line, " ");
    int i=0;
    while(tokens != NULL && i<SUDOKU_SIZE){
    	// convert string to integer
        array[i++] = (int) (*tokens - '0');
        tokens = strtok(NULL, " ");
    }
}

void *check_all_rows(void *arg){
	// loop through each row
	for(int j=0; j<SUDOKU_SIZE; j++){
		if(check_row(j)!=1){
			valid[9] = 0;
			return NULL;
		}
	}
	valid[9] = 1;
	return NULL;
}

int check_row(int row){
	int s[2];
	// loop for each possible number (1-9)
	for(s[0]=1; s[0]<=SUDOKU_SIZE; s[0]++){
		// count of s[0] occurences
		s[1]=0;
		// loop through each element of the row
		for(int i=0; i<SUDOKU_SIZE; i++){
			if(puzzle[row][i]==s[0]){
				s[1]++;
			}
		}
		if(s[1]!=1){
			return 0;
		}
	}
	return 1;
}

void *check_all_columns(void *arg){
	// loop through each column
	for(int j=0; j<SUDOKU_SIZE; j++){
		if(check_column(j)!=1){
			valid[10] = 0;
			return NULL;
		}
	}
	valid[10] = 1;
	return NULL;
}

int check_column(int col){
	int s[2];
	// loop for each possible number (1-9)
	for(s[0]=1; s[0]<=SUDOKU_SIZE; s[0]++){
		// count of s[0] occurences
		s[1]=0;
		// loop through each element of the column
		for(int i=0; i<SUDOKU_SIZE; i++){
			if(puzzle[i][col]==s[0]){
				s[1]++;
			}
		}
		if(s[1]!=1){\
			return 0;
		}
	}
	return 1;
}

void *check_all_grids(void *arg){
	// loop through grids
	for(int i=0; i<SUDOKU_SIZE; i++){
		if(check_grid((i%3)*3,(i/3)*3)!=1){
			valid[i] = 0;
			return NULL;
		} else {
			valid[i]=1;
		}
	}
	return NULL;
}

check_grid(int row, int col){
	int s[2];
	// loop for each possible number (1-9)
	for(s[0]=1; s[0]<=SUDOKU_SIZE; s[0]++){
		// count of s[0] occurences
		s[1]=0;
		// loop through each element of the grid
		for(int i=row; i<=row+2; i++){
			for(int j=col; j<=col+2; j++){
				if(puzzle[i][j]==s[0]){
					// increment # of occurences if s[0] is found
					s[1]++;
				}
			}
		}
		// check if s[0] has a valid number of occurences
		if(s[1]!=1){
			return 0;
		}
	}
	return 1;
}
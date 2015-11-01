#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include "sudoku_validator.h"

#define SUDOKU_SIZE 9
#define NUM_THREADS 3
#define BUFFER_LEN 256

int puzzle[SUDOKU_SIZE][SUDOKU_SIZE];
int flag[SUDOKU_SIZE][SUDOKU_SIZE];
int valid[NUM_THREADS] = {0};
//valid[0] = row, valid[1] = column, valid[2] = grid

typedef struct{
	int row;
	int column;
} parameters;

void* checkGrid(void* pos){
	
	parameters* position = (parameters*)pos;

	int row = position->row;
	int col = position->column;

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
	 	if(s[1]>1){
	 		valid[2] = 0;
		}
	}
	valid[2] = 1;
	return NULL;
}

void* checkCol(void* col){
	
	int* colNum = (int*)col;

	int s[2];
	//Loop for each possible number (1-9)
	for(s[0] = 1; s[0] <= SUDOKU_SIZE; s[0]++){
		//Count of s[0] occurences
		s[1] = 0;
		//Loop through each element of the column
		for(int rowNum = 0; rowNum < SUDOKU_SIZE; rowNum++){
			if(puzzle[rowNum][*colNum] == s[0]){
				s[1]++;
			}
		}
		//Return 0 if not valid
		if(s[1] > 1){
			valid[1] = 0;
		}
	}
	//Return 1 if valid
	valid[1] = 1;
	return NULL;
}

void* checkRow(void* row){
	
	int* rowNum = (int*)row;

	int s[2];
	//Loop for each possible number (1-9)
	for(s[0]=1; s[0]<=SUDOKU_SIZE; s[0]++){
		//Count of s[0] occurences
		s[1]=0;
		//Loop through each element of the row
		for(int colNum = 0; colNum < SUDOKU_SIZE; colNum++){
			if(puzzle[*rowNum][colNum]==s[0]){
				s[1]++;
			}
		}
		//Return 0 if not valid
		if(s[1]>1){
			valid[0] = 0;
		}
	}
	//Return 1 if valid
	valid[0] = 1;
	return NULL;
}

bool checkValid(parameters position){
	//Create three threads. One for row, one for column, one for grid
	pthread_t pth[NUM_THREADS];

	//Check if the row, column and 3x3 grid are valid
	//This check will be based on the index of the current position
	pthread_create(&pth[0], 0, checkRow, (void *)&position.row);
	pthread_create(&pth[1], 0, checkCol, (void *)&position.column);
	pthread_create(&pth[2], 0, checkGrid, (void *)&position);

	//Join the check threads
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(pth[i], NULL);
	}
	
	//Check if the insertion was valid
	for(int i = 0; i < NUM_THREADS; i++){
		if(valid[i] == 0){
			return false;
		}
	}
	return true;
}

void solvePuzzle(){
	//Start the solver's position at the top left corner.
	//Top left corner will be [0][0]
	//Top right corner will be [0][9]
	//Bottom left corner will be [9][0]
	//Bottom right corner will be [9][9]
	parameters position;
	position.row = 0;
	position.column = 0;
	bool valid;
	bool movForw = true;
	int insertVal;

	while(position.row < (SUDOKU_SIZE-1)){
		
		valid = false;
		insertVal = puzzle[position.row][position.column];
		while(insertVal < SUDOKU_SIZE){
			
			//Adds one to insertVal every iteration
			//Adds one at start since insertVal needs to
			//Skip over 0 or a previous val already inserted
			insertVal++;

			//Insert a value into the position if it isn't a flag
			if(flag[position.row][position.column] != 0){
				puzzle[position.row][position.column] = insertVal; 
			} else{
				//Skips over the value retaining movForw's value
				//So it moves backward or forward
				break;
			}

			valid = checkValid(position);
			if(valid == true){
				movForw = true;
				break;
			}
			if(valid == false && insertVal == SUDOKU_SIZE){
				//Go back one in the position
				movForw = false;
			}
		}

		if(movForw == true){ //Move forward if an insertion was done
			//If there are columns left, add one to columns
			//Otherwise move down a row and set columns to 0
			if(position.column < (SUDOKU_SIZE-1)){
				position.column++;
			}else{
				position.column = 0;
				position.row++;
			}
		} else{ //Move backwards if an insertion runs out of nums
			if(position.column > 0){
				position.column--;
			}else{
				position.column = (SUDOKU_SIZE-1);
				position.row--;
			}
		}
	}
}























//EVERYTHING BELOW THIS POINT WORKS

void printPuzzle(){
	//Prints a bar before the entire puzzle has been printed
	printf("=========================\n");
	//Loops through the rows
	for(int rowNum = 0; rowNum < SUDOKU_SIZE; rowNum++){
		//Loops through the columns
		for(int colNum = 0; colNum < SUDOKU_SIZE; colNum++){
			//If the element is at the end of the row, don't add a ","
			//Else print normally
			if(colNum == (SUDOKU_SIZE - 1)){
				printf("%d", puzzle[rowNum][colNum]);
			} else{
				printf("%d, ", puzzle[rowNum][colNum]);
			}	
		}
		//Prints an endline after all the columns in a row have been printed
		printf("\n");
	}
	//Prints a bar after the entire puzzle has been printed
	printf("=========================\n");
}

void tokenize(char *line, int *array){
	//Change end of line character for tokenizer
    char *newLine = strstr(line, "\n");
    if(newLine != NULL){
        *newLine = ' ';
    }

    //Break line into strings separated by spaces
    char *tokens = strtok(line, " ");
    int i=0;
    while(tokens != NULL && i<SUDOKU_SIZE){
    	//Convert string to integer
        array[i++] = (int) (*tokens - '0');
        tokens = strtok(NULL, " ");
    }
}

bool loadPuzzle(char* filename){

	//Opens the file in read mode
	FILE *fp;
	fp = fopen(filename, "r");

	//Row number
	int rowNum = 0;
	//The entire line from the file
	char line[BUFFER_LEN];
	//The row of the sudoku puzzle
	int row[SUDOKU_SIZE] = { 0 };

	//Checks if the file is valid or not
	if(fp == NULL){
    	printf("Error reading file.\n");
    	return false;
    } else{
    	//Loops until end of file
    	//Takes the line of the file and stores it into line
    	while(fgets(line, BUFFER_LEN, fp)){
    		
    		//Tokenizes the line into the row array
    		//ie. line = "1 2 3 4 5 6 7 8 9" -> row[0] = 1, row[1] = 2, etc.
    		tokenize(line, row);

    		//Assigns elements in the row to their places in puzzle
    		for(int colNum = 0; colNum < SUDOKU_SIZE; colNum++){
    			puzzle[rowNum][colNum] = row[colNum];
<<<<<<< HEAD
    			flag[rowNum][colNum] = row[colNum]!=0;
=======
    			//Make the flags
    			flag[rowNum][colNum] = row[colNum] != 0;
>>>>>>> c7067df40eb4d3b274fbcb2941b90df081c3ba89
    		}
    		rowNum++;
		}
        fclose(fp);
    }
    return true;
}

int main(){

	//Allows for this to be easily changed into user input if needed
	char* filename = "puzzle.txt";

	//Loads the puzzle from the file into the global puzzle array
	//If the load is successful, the rest of the code is executed
	if(loadPuzzle(filename)){

		//Prints the unsolved puzzle
		printPuzzle();

		//Indicates when the solver starts		------ REMOVE AFTER TESTING
		printf("Starting Solver\n");
		//Solves the puzzle
		solvePuzzle();
		//Indicates when the solver finishes	------ REMOVE AFTER TESTING
		printf("Finished Solver\n");

		//Prints the solved puzzle
		printPuzzle();
	}
}

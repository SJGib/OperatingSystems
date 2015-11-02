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

void writePuzzle(){
	
	FILE* file = fopen("solution.txt", "w");

	for(int rowNum = 0; rowNum < SUDOKU_SIZE; rowNum++){
		//Loops through the columns
		for(int colNum = 0; colNum < SUDOKU_SIZE; colNum++){
			//Prints the elements to file with a space between each element
			//If it's the end of the line, don't add a space
			if(colNum == (SUDOKU_SIZE - 1)){
				fprintf(file, "%d", puzzle[rowNum][colNum]);
			} else{
				fprintf(file, "%d ", puzzle[rowNum][colNum]);
			}	
		}
		//Prints an endline after all the columns in a row have been printed
		fprintf(file, "\n");
	}
	fclose(file);
}

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

void* checkGrid(void* pos){
	
	parameters* position = (parameters*)pos;
	int numOcc[SUDOKU_SIZE] = { 0 };
	int rowNum = position->row;
	int colNum = position->column;
	int rowStart;
	int colStart;
	bool checkPass = true;

	//Pick which 3x3 grid the position is in
	//0-2 = 1, 3-5 = 2, 6-8 = 3
	if(rowNum < 3){
		rowStart = 0;
	} else if(rowNum < 6){
		rowStart = 3;
	} else{
		rowStart = 6;
	}

	if(colNum < 3){
		colStart = 0;
	} else if(colNum < 6){
		colStart = 3;
	} else{
		colStart = 6;
	}

	//Loop for each possible number (1-9)
	for(int checkVal = 1; checkVal < (SUDOKU_SIZE+1); checkVal++){
	 	//Loop through each element of the 3x3 grid
	 	for(int i = rowStart; i < rowStart + 3; i++){
	 		for(int j = colStart; j < colStart + 3; j++){
	 			if(puzzle[i][j] == checkVal){
	 				//Increment # of occurences if checkVal is found
	 				numOcc[checkVal-1]++;
	 			}
	 		}
	 	}
	}
	//If the number of occurences of any value is
	//greater than 1, than the check fails and the
	//inputted value needs to be changed
	for(int i = 0; i < SUDOKU_SIZE; i++){
 		if(numOcc[i] > 1){
 			checkPass = false;
 		}
 	}
 	if(checkPass == true){
 		valid[2] = 1;
 	} else{
 		valid[2] = 0;
 	}
	return NULL;
}

void* checkCol(void* col){
	
	int* colNum = (int*)col;
	int numOcc[SUDOKU_SIZE] = { 0 };
	bool checkPass = true;

	//Loop for each possible number (1-9)
	for(int checkVal = 1; checkVal < (SUDOKU_SIZE+1); checkVal++){
		//Loop through each element of the column
		for(int rowNum = 0; rowNum < SUDOKU_SIZE; rowNum++){
			if(puzzle[rowNum][*colNum] == checkVal){
				numOcc[checkVal-1]++;
			}
		}
	}
	//If the number of occurences of any value is
	//greater than 1, than the check fails and the
	//inputted value needs to be changed
	for(int i = 0; i < SUDOKU_SIZE; i++){
 		if(numOcc[i] > 1){
 			checkPass = false;
 		}
 	}
 	if(checkPass == true){
 		valid[1] = 1;
 	} else{
 		valid[1] = 0;
 	}
	return NULL;
}

void* checkRow(void* row){
	
	int* rowNum = (int*)row;
	int numOcc[SUDOKU_SIZE] = { 0 };
	bool checkPass = true;

	//Loop for each possible number (1-9)
	for(int checkVal = 1; checkVal < (SUDOKU_SIZE+1); checkVal++){
		//Loop through each element of the row
		for(int colNum = 0; colNum < SUDOKU_SIZE; colNum++){
			if(puzzle[*rowNum][colNum] == checkVal){
				numOcc[checkVal-1]++;
			}
		}
	}
	//If the number of occurences of any value is
	//greater than 1, than the check fails and the
	//inputted value needs to be changed
	for(int i = 0; i < SUDOKU_SIZE; i++){
 		if(numOcc[i] > 1){
 			checkPass = false;
 		}
 	}
 	if(checkPass == true){
 		valid[0] = 1;
 	} else{
 		valid[0] = 0;
 	}
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

	while(position.row < SUDOKU_SIZE){
		
		valid = false;
		insertVal = puzzle[position.row][position.column];

		while(insertVal < SUDOKU_SIZE){
			//Adds one to insertVal every iteration
			//Adds one at start since insertVal needs to
			//Skip over 0 or a previous val already inserted
			insertVal++;

			//Insert a value into the position
			//Only inserts if it's not a flag
			if(flag[position.row][position.column] == 0){				
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
				//Changes the position's value to 0 knowing that the input
				//value in it is wrong so the previous elements are not
				//affected during the checks
				puzzle[position.row][position.column] = 0;
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

			//Boundary case if it needs to move back when a val is 9
			if(insertVal == SUDOKU_SIZE && (flag[position.row][position.column] == 0)){
				puzzle[position.row][position.column] = 0;
			}

			if(position.column > 0){
				position.column--;
			}else{
				position.column = (SUDOKU_SIZE-1);
				position.row--;
			}
		}
	}
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
    			//Make the flags
    			flag[rowNum][colNum] = row[colNum] != 0;
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

		printf("Unsolved Puzzle\n");
		//Prints the unsolved puzzle
		printPuzzle();
		//Solves the puzzle
		solvePuzzle();
		printf("Solved Puzzle\n");
		//Prints the solved puzzle
		printPuzzle();
		//Writes the puzzle to file
		writePuzzle();
	}
}
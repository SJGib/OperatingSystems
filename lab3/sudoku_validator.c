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

void tokenize(char *buffer, char *command, char *arg){
    char *newLine = strstr(buffer, "\n");
    if(newLine != NULL){
        *newLine = 0;
    }

    char *tokens = strtok(buffer, " ");
    strncpy(command, tokens, BUFFER_LEN);
    tokens = strtok(NULL, " ");

    while(tokens != NULL)
    {
        strcat(arg, tokens);
        tokens = strtok(NULL, " ");
        if(tokens!=NULL){
            strcat(arg, " ");
        }
    }
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
	initials[9].row = 0;
	initials[9].column = 0;

	//col check
	initials[10].row = 0;
	initials[10].column = 0;

	//start segment checks
	for(int i = 0; i < 9; i++){
		pthread_create(&pth[i], 0, check_grid, (void *)&initials[i]);
	}
	pthread_create(&pth[9], 0, check_row, (void *)&initials[9]);
	pthread_create(&pth[10], 0, check_column, (void *)&initials[10]);


	//join segments
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(pth[i], NULL);
	}
}

void init(){
	FILE *fp;
	fp = fopen("puzzle.txt", "r");
	int i = 0;
	int j = 0;

   	char line[BUFFER_LEN];

    if(fp == NULL){
    	printf("Error reading file.\n");
    } else{
    	while(fgets(line, BUFFER_LEN, fp)){
    		puzzle[i][j] = tokenize(line);

    		i++;
		}
        fclose(fp);
    }

}

void *check_row(void *arg){
	parameters *init = (parameters *) arg;
	int s[2];
	// loop through each row
	for(int j=0; j<SUDOKU_SIZE; j++){
		// loop 1-9 checking # of occurences
		for(s[0]=1; s[0]<=SUDOKU_SIZE; s[0]++){
			for(int i=0; i<SUDOKU_SIZE; i++){
				if(puzzle[j][i]==s[0]){
					s[1]++;
				}
			}
			if(s[1]!=1){
				valid[9] = 0;
				return NULL;
			}
		}
	}
	valid[9] = 1;
	return NULL;
}

void *check_column(void *arg){
	parameters *init = (parameters *) arg;
	int s[2];
	// loop through each column
	for(int j=0; j<SUDOKU_SIZE; j++){
		// loop 1-9 checking # of occurences
		for(s[0]=1; s[0]<=SUDOKU_SIZE; s[0]++){
			for(int i=0; i<SUDOKU_SIZE; i++){
				if(puzzle[i][j]==s[0]){
					s[1]++;
				}
			}
			if(s[1]!=1){
				valid[10] = 0;
				return NULL;
			}
		}
	}
	valid[10] = 1;
	return NULL;
}

void *check_grid(void *arg){
	parameters *init = (parameters *) arg;
	int s[2];
	// loop 1-9 checking # of occurences
	for(s[0]=1; s[0]<=SUDOKU_SIZE; s[0]++){
		// initialize occurences of s[0] to 0
		s[1]=0;
		// check each element
		for(int i=init->row; i<init->row+2; i++){
			for(int j=init->column; j<init->column+2; j++){
				if(puzzle[i][j]==s[0]){
					// increment # of occurences if s[0] is found
					s[1]++;
				}
			}
		}
		// check if s[0] has a valid number of occurences
		if(s[1]!=1){
			valid[(init->row/3)+init->column]=0;
			return NULL;
		}
	}
	valid[(init->row/3)+init->column]=1;

	return NULL;
}
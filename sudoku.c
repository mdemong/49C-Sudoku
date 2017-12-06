
/* 
 * File:   sudoku.c
 * Authors: mdemong, gareiner
 */

#include <stdio.h>
#include <stdlib.h>

int checkMatches(int grid[][9], int row, int col, int x);
int solveSudoku(int grid[][9], int row, int col);
void generatePuzzle(int a[9][9]);
void printPuzzle(const int a[9][9]);
void shuffleRows(int a[9][9]);
void shuffleColumns(int a[9][9]);
void shuffleChunks(int a[9][9]);
void swap(int a[][9], int i1, int j1, int i2, int j2);

/*
 * 
 */
int main(int argc, char** argv) {
    printf("Running Demo\n");
    printf("Generating Puzzle:\n");
    int p[9][9] = {};
    generatePuzzle(p);
    printPuzzle(p);
    printf("Solving Puzzle:\n");
    solveSudoku(p, 0, 0);
    printPuzzle(p);
}

void generatePuzzle(int a[9][9]){
    //TODO: Replace this with actual generation, lol.
    int b[9][9] = { 
	{ 3, 0, 6, 5, 0, 8, 4, 0, 0 },
	{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
	{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
	{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
	{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
	{ 1, 3, 0, 0, 0, 0, 2, 5, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
	{ 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    
    //replacing elements of a with elements of b
    //interestingly, doing a = { . . . } does not work here.
    //elements must be transferred manually.
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            a[i][j] = b[i][j];
    }
}
/**
 * Helper function which shuffles rows of a 9x9 2D array.
 * @param a
 */
void shuffleRows(int a[9][9]){
    for(int i = 0; i < 20; i++){
        //shuffling first 3 rows
        int a = rand() % 3;
        //shuffling second 3 rows

        //shuffling last 3 rows

    }
    
}

void shuffleColumns(int a[9][9]){
    //shuffling first 3 columns
    
    //shuffling second 3 columns
    
    //shuffling last 3 columns
    
}

void shuffleChunks(int a[9][9]){
    //shuffling rows
    
    //shuffling columns
}

/**
 * Helper function to swap two values of the sudoku board.
 * @param a the array to swap values in
 * @param i1 the row of value 1
 * @param j1 the column of value 1
 * @param i2 the row of value 2
 * @param j2 the column of value 2
 */
void swap(int a[9][9], int i1, int j1, int i2, int j2){
    int temp = a[i1][j1];
    a[i1][j1] = a[i2][j2];
    a[i2][j2] = temp;
}

//Recursive solver function
int solveSudoku(int grid[][9], int row, int col)
{
	//Ends recursion when all numbers < 9 have been tried in each empty cell of the Sudoku board
	if (row < 9 && col < 9)
	{
		if (grid[row][col] != 0)
		{
			if ((col + 1) < 9) {
				return solveSudoku(grid, row, col + 1);
			}
			else if ((row + 1) < 9) {
				return solveSudoku(grid, row + 1, 0); 
			}
			else return 1;
		}
		else
		{
			//For every number < 9, try placing them in each row and column
			for (int i = 0; i < 9; i++)
			{
				//If no matches in row, column, or 3x3 sub-grid
				if (checkMatches(grid, row, col, i + 1))
				{
					//Try new numbers that are < 9 in column
					grid[row][col] = i + 1;
					if ((col + 1) < 9)
					{
						if (solveSudoku(grid, row, col + 1)) {
							return 1;
						}
						else grid[row][col] = 0;
					}
					//Try new numbers that are < 9 in row
					else if ((row + 1) < 9)
					{
						if (solveSudoku(grid, row + 1, 0)) {
							return 1;
						}
						else {
							grid[row][col] = 0;
						}
					}
					else return 1;
				}
			}
		}
		return 0;
	}
	else {
		return 1;
	}
}

//Helper function to check if rows, columns, and 3x3 sub-grids have matches
int checkMatches(int grid[][9], int row, int col, int x)
{
	//Generate row portion of 3x3 sub-grid
	int rowSubGrid = (row / 3) * 3;
	//Generate column portion of 3x3 sub-grid
	int colSubGrid = (col / 3) * 3;
	for (int i = 0; i < 9; i++) {
		//If row has match, return false
		if (grid[row][i] == x) {
			return 0;
		}
		//If column has match, return false
		if (grid[i][col] == x) { 
			return 0; 
		}
		//If 3x3 sub-grid has match, return false
		if (grid[rowSubGrid + (i % 3)][colSubGrid + (i / 3)] == x) {
			return 0;
		}
	}
	return 1;
}

void printPuzzle(const int a[9][9]){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%2d", a[i][j]);
        }
        printf("\n");
    }
}
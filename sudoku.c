
/* 
 * File:   sudoku.c
 * Authors: mdemong, gareiner
 */

#include <stdio.h>

int checkMatches(int grid[][9], int row, int col, int x);
int solveSudoku(int grid[][9], int row, int col);
void generatePuzzle(int a[9][9]);
void printPuzzle(const int a[9][9]);

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
    //TODO: Replace this method
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

void printPuzzle(const int a[9][9]){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%2d", a[i][j]);
        }
        printf("\n");
    }
}
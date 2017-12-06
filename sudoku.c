
/* 
 * File:   Sudoku.c
 * Authors: Micah Demong, Geordi Reiner
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int checkMatches(int grid[][9], int row, int col, int x);
int solveSudoku(int grid[][9], int row, int col);
void generatePuzzle(int a[9][9]);
void printPuzzle(const int a[9][9]);
void shuffleRows(int a[9][9]);
void shuffleColumns(int a[9][9]);
void shuffleChunks(int a[9][9]);
void swap(int a[][9], int i1, int j1, int i2, int j2);
void swapChunks(int a[9][9], int row1, int col1, int row2, int col2);
void zeroRandomVals(int a[9][9], int n);

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

/**
 * Generates a Sudoku puzzle.
 * @param a a 9x9 2D array, which will become a sudoku board.
 */
void generatePuzzle(int a[9][9]){
    // Seeding Random Number from time
    srand ( time(NULL) );
    int seed[9][9] = { 
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9 },
	{ 7, 8, 9, 1, 2, 3, 4, 5, 6 },
	{ 4, 5, 6, 7, 8, 9, 1, 2, 3 },
	{ 9, 1, 2, 3, 4, 5, 6, 7, 8 },
	{ 3, 4, 5, 6, 7, 8, 9, 1, 2 },
	{ 6, 7, 8, 9, 1, 2, 3, 4, 5 },
	{ 8, 9, 1, 2, 3, 4, 5, 6, 7 },
	{ 2, 3, 4, 5, 6, 7, 8, 9, 1 },
	{ 5, 6, 7, 8, 9, 1, 2, 3, 4 } };
    
    //replacing elements of a with elements of b
    //doing a = { . . . } does not work here.
    //elements must be transferred manually.
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            a[i][j] = seed[i][j];
    }
    
    // Shuffling
    for (int i = 0; i < 1000; i++)
    {
        shuffleRows(a);
        shuffleColumns(a);
        shuffleChunks(a);
    }
    
    zeroRandomVals(a,36);
    
}

/**
 * Shuffles rows of the puzzle.
 * @param a the sudoku puzzle
 */
void shuffleRows(int a[9][9])
{
    for (int i = 0; i < 3; i++) // 3 sets of swaps
    {
        //Within each chunk row. Top, Middle, Bottom.
        //Top starts at 0, middle starts at 3, bottom starts at 6
        for (int offset = 0; offset < 9; offset += 3)
        {
            int toprow = (rand() % 3) + offset;
            int bottomrow = ((toprow + 1) % 3) + offset;
            //Performing vertical swap at each column
            for (int col = 0; col < 9; col++)
            {
                swap(a, toprow, col, bottomrow, col);
            }
        }
    }
}

/**
 * Shuffles the columns of the puzzle.
 * @param a the sudoku puzzle
 */
void shuffleColumns(int a[9][9])
{
    for (int i = 0; i < 3; i++) // 3 sets of swaps
    {
        //Within each chunk column. Left, Middle, Right
        //Left starts at 0, middle starts at 3, right starts at 6
        for (int offset = 0; offset < 9; offset += 3)
        {
            int leftcol = (rand() % 3) + offset;
            int rightcol = ((leftcol + 1) % 3) + offset;
            //Performing horizontal swap at each row
            for (int row = 0; row < 9; row++)
            {
                swap(a, row, leftcol, row, rightcol);
            }
        }
    }
}

/**
 * Shuffles the 3x3 chunks of the puzzle.
 * @param a the puzzle
 */
void shuffleChunks(int a[9][9])
{
    for (int i = 0; i < 10; i++)
    {
        // Swapping random chunk rows
        int toprow = 3 * (rand() % 3);
        int bottomrow = ((toprow + 3) % 9);
        for(int i = 0; i <= 6; i += 3)
        {
            swapChunks(a, toprow, i, bottomrow, i);
        }
        // Swapping random chunk columns
        int topcol = 3 * (rand() % 3);
        int bottomcol = ((topcol + 3) % 9);
        for(int i = 0; i <= 6; i += 3)
        {
            swapChunks(a, i, topcol, i, bottomcol);
        }
    }
}

/**
 * Helper function which swaps two 3x3 chunks.
 * @param a the Sudoku puzzle
 * @param row1 the row of top left corner of chunk 1
 * @param col1 the column of the top left corner of chunk 1
 * @param row2 the row of the top left corner of chunk 2
 * @param col2 the column of the top left corner of chunk 2
 */
void swapChunks(int a[][9], int row1, int col1, int row2, int col2)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            swap(a, row1 + i, col1 + j, row2 + i, col2 + j);
        }
    }
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

/**
 * Changes the specified number of random elements to zeros.
 * @param a the 9x9 Sudoku board
 * @param n the number of elements to zero
 */
void zeroRandomVals(int a[9][9], int n){
    int i = 0;
    while (i < n && i < 81)
    {
        int row = rand() % 9;
        int col = rand() % 9;
        if(a[row][col] != 0){
            i++;
            a[row][col] = 0;
        }
    }

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

/**
 * Prints out the puzzle.
 * @param a the Sudoku puzzle
 */
void printPuzzle(const int a[9][9]){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%2d", a[i][j]);
        }
        printf("\n");
    }
}
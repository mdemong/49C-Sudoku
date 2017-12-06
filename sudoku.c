
/* 
 * File:   sudoku.c
 * Authors: mdemong, gareiner
 */

#include <stdio.h>

void generatePuzzle(int a[9][9]);
void solvePuzzle(int a[9][9]);
void printPuzzle(const int a[9][9]);

/*
 * 
 */
int main(int argc, char** argv) {
    printf("Running Demo\n");
    printf("Generating Puzzle:\n");
    int p[9][9];
    generatePuzzle(p);
    printPuzzle(p);
    printf("Solving Puzzle:\n");
    solvePuzzle(p);
    printPuzzle(p);
}

void generatePuzzle(int a[9][9]){
    
}

void solvePuzzle(int a[9][9]){
    
}

void printPuzzle(const int a[9][9]){
    
}


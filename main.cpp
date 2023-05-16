#include <iostream>
using namespace std;

// Constants
const int SIZE = 9;

// Function to print the Sudoku grid
void printGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in a given cell
bool canPlace(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check if the number is already present in the current row
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // Check if the number is already present in the current column
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number is already present in the current 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[SIZE][SIZE]) {
    // Find an empty cell
    int row = -1;
    int col = -1;
    bool isEmptyCell = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                isEmptyCell = true;
                break;
            }
        }
        if (isEmptyCell) {
            break;
        }
    }

    // If no empty cell is found, the Sudoku puzzle is solved
    if (!isEmptyCell) {
        return true;
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= SIZE; num++) {
        if (canPlace(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0; // Backtrack if the number doesn't lead to a solution
        }
    }

    return false;
}

int main() {
    int grid[SIZE][SIZE] = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    cout << "Sudoku grid before solving:" << endl;
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << endl << "Sudoku grid after solving:" << endl;
        printGrid(grid);
    } else {
        cout << endl << "No solution exists." << endl;
    }

    return 0;
}
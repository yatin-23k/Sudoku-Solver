#include<iostream>
#include<fstream>
#include<bitset>
using namespace std;

# define n 9

int grid[n][n];

// Create 1D arrays to hold binary representation of the digits in each row, column, and 3x3 box
int rowDigits[9]={0};
int colDigits[9]={0};
int boxDigits[9]={0};

/*
 * Function to input a Sudoku problem from a text file. 
*/
bool inputMatrix() {
    ifstream input_file("sudoku.txt");
    if (!input_file) {
        cerr << "Error opening file\n";
        return false;
    }

    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            input_file >> grid[i][j];

    input_file.close();

    return true;
}

/*
 * Function to print a Sudoku grid in a readable format. 
*/
void printMatrix() {
    for(int i = 0; i < 9; i++) {
        if(i % 3 == 0 && i != 0) {
            cout << "------+-------+------\n";
        }
        for(int j = 0; j < 9; ++j) {
            if(j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}

/*
 * Function to write the Sudoku solution to a text file.
*/
void outputMatrix() {
    ofstream output_file("sudoku_solution.txt");
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; ++j) {
            output_file << grid[i][j] << ' ';
        }
        output_file << '\n';
    }
    output_file.close();
}

/*
 * This function calculates the index of a 3x3 box in the Sudoku grid given a cell's coordinates.
 */
int boxIndex(int x, int y)
{
    return ( (x / 3) * 3 )+ (y / 3);
}

/*
 * This function initializes the binary representations of the digits in each row, column, and 3x3 box based on the input Sudoku grid.
 */
void setInitialValue()
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            // Check if a cell is filled
            if(grid[i][j] > 0){
                // Update the binary representation of the digits for the corresponding row, column, and 3x3 box
                rowDigits[i] |= 1 << (grid[i][j] - 1);
                colDigits[j] |= 1 << (grid[i][j] - 1);
                boxDigits[boxIndex(i, j)] |= 1 << (grid[i][j] - 1);
            }
        }
    }
}

/*
 * Function to check if a number placed in a specific position is valid according to Sudoku rules.
*/
bool safeState(int row, int col, int digit)
{
    if (!((boxDigits[boxIndex(row, col)] & digit) || (rowDigits[row] & digit) || (colDigits[col] & digit))){
        return true;
    }
    return false;
}

/*
 * Recursive function to solve the Sudoku problem.
 */
bool sudokuSolution(int row, int col)
{
    // Base case: if we've reached the end of the grid
    if(row == n-1 && col == n)
        return true;
    
    // If we've reached the end of a row, move to the next row
    if(col == n ){
        col = 0;
        row++;
    }

    // If a cell is already filled, move to the next cell
    if(grid[row][col] != 0)
        return sudokuSolution(row, col + 1);
    
    // Try filling the cell with digits from 1 to 9
    for(int i = 1; i <= n; i++){
        int digit = 1 << (i - 1);
        // If the digit can be placed at the cell
        if(safeState(row, col, digit)){
            // Place the digit at the cell and update the binary representations
            grid[row][col] = i;
            boxDigits[boxIndex(row, col)] |= digit;
            rowDigits[row] |= digit;
            colDigits[col] |= digit;

            // Move to the next cell
            if(sudokuSolution(row, col + 1))
                return true;

            // If placing the digit at the cell does not lead to a solution, remove the digit from the cell and backtrack
            grid[row][col] = 0;
            boxDigits[boxIndex(row, col)] &= ~digit;
            rowDigits[row] &= ~digit;
            colDigits[col] &= ~digit;
        }       
    }
    // If no digit can be placed at the cell, return false
    return false;
}

int main()
{
    if (!inputMatrix()) return 0;
    
    cout << "Input Sudoku:\n\n";
    printMatrix();

    setInitialValue();

    bool solution = sudokuSolution(0, 0);

    if(solution) {
        cout << "\nSolved Sudoku:\n\n";
        printMatrix();
        cout << "\n\n Do you want to save the solution to a file? (y/n): ";
        char ch;
        cin >> ch;
        if(ch == 'y' || ch == 'Y') outputMatrix();
    } 
    else {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}


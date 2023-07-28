# Sudoku Solver Project

## 1. INTRODUCTION:

In this project, I implemented a Sudoku solver using three different algorithms and conducted a comprehensive performance comparison using execution time across varying puzzle complexities. The aim of this project is to provide insights for efficient Sudoku-solving strategies. The first algorithm utilizes a simple backtracking approach to solve the Sudoku puzzles. The second algorithm optimizes the process using bitwise operations to solve the Sudoku. The third algorithm is an optimization of simple backtracking and uses Cross Hatching Technique to solve Sudoku puzzles.

## 2. RULES OF SUDOKU PUZZLE:

Sudoku is a logic-based number-placement puzzle, where the goal is to fill a 9x9 grid with digits from 1 to 9, subject to certain constraints. The constraints are:

1. Grid Size: Sudoku is played on a 9x9 grid divided into nine 3x3 subgrids called boxes.
2. Digits: The digits 1 to 9 must be filled in the grid. Each row, column, and box must contain all the digits from 1 to 9 exactly once.
3. Row Constraint: Each row in the grid must contain all the digits from 1 to 9 exactly once.
4. Column Constraint: Each column in the grid must contain all the digits from 1 to 9 exactly once.
5. Box Constraint: Each 3x3 box in the grid must contain all the digits from 1 to 9 exactly once.
6. Initial Values: Some cells in the grid are pre-filled with initial values (given clues) that cannot be changed.
7. Unique Solution: A valid Sudoku puzzle should have a unique solution. There should not be multiple ways to fill the grid while satisfying the Sudoku constraints.
8. No Repetition: No digit can be repeated within a row, column, or box. Each cell must have a distinct value.

## 3. ALGORITHMS USED:

### Simple Backtracking

The basic approach of this algorithm is as follows:

1. Start by finding an empty cell in the Sudoku grid.
2. Try assigning each number from 1 to 9 to the empty cell.
3. Before assigning a number, check whether it is safe to assign. Ensure the same number is not present in the current row, current column, and the 3x3 subgrid that contains the cell.
4. If it is safe to assign, make the assignment and move to the next empty cell recursively.
5. If the assignment doesn't lead to a solution, backtrack and try the next number for the current empty cell.
6. Repeat this process until all cells are filled or no solution is possible.

### Backtracking with Bitwise Operations:

In this algorithm, we optimize the isSafe function using bitwise operations for O(1) checks. The rest of the process is the same as simple backtracking. The steps are as follows:

1. Create three arrays of size N (N = 9) for rows, columns, and boxes. The boxes are indexed from 0 to 8 (identified by row / 3 * 3 + column / 3).
2. Map the initial values of the Sudoku grid.
3. Each time we add/remove an element to/from the grid, we set the corresponding bits to 1 or 0 in the bitmasks of rows, columns, and boxes.
4. The isSafe function then checks the corresponding bitmasks to determine if a number can be safely assigned to a cell, eliminating the need for repetitive checks.

### Backtracking with Cross Hatching:

This algorithm is an optimization of the Simple Backtracking method and runs faster due to better pruning. The idea is to fill Sudoku by first identifying the element which is almost filled. It starts with identifying the row and column where the element should be placed. Picking the almost-filled elements first will give better pruning. The steps are as follows:

1. Start by identifying the row and column with the most filled elements (almost-filled elements).
2. Pick the element with the fewest possibilities to place first, which helps in better pruning.
3. Proceed with the same backtracking approach as in the Simple Backtracking algorithm, but with better selection of cells to fill.

### Time and Space Complexities:

The upper bound of Time Complexity of each algorithm used is O(9^(n*n)). But the number of recursive calls is different in each algorithm, thereby resulting in different execution time. Although we are using 3 additional arrays of size n in the bitwise algorithm and numerous data structures of different sizes in Cross Hatching algorithm, the upper bound of the space complexity still remains O(n^2) in each algorithm because of the Sudoku matrix we are using to store and output digits in each algorithm.

## 4. COMPARISON

The Comparison of the three algorithms is done in terms of their execution time.
![sudokuSolverLineGraph](https://github.com/yatin-23k/Sudoku-Solver/assets/137977262/215edbca-3209-4fc7-80b1-e5c217088d2f)
![sudokuSolverBarGraph](https://github.com/yatin-23k/Sudoku-Solver/assets/137977262/704143d7-3fba-45f3-ab92-a009acbbeb89)

## 5. Usage

**Step 1: Input the Sudoku Puzzle**

Begin by inputting the 9x9 matrix representing the Sudoku puzzle in the file 'sudoku.txt'. Use 0 to indicate the empty positions that need to be solved.

**Step 2: Run the program**

Run the desired program using a C++ compiler of your choice.

**Step 3: Display of the Initial Puzzle**

The initial Sudoku puzzle is displayed to ensure that the input has been correctly read from the file. It will help the user verify that the provided digits match the intended puzzle.

**Step 4: Execution of the Sudoku Solver**

The Sudoku Solver code is executed to find a solution to the puzzle. The solver will analyze the initial configuration and attempt to fill in the missing digits following the Sudoku rules.

**Step 5: Display the Solved Puzzle**

If the Sudoku Solver finds a valid solution, the program will present the user with the option to write the output to a designated output file. The user can type 'y' or 'Y' to agree or any other key to disagree. If the Sudoku Solver fails to find a solution, there might be conflicting or unsolvable conditions in the puzzle. You may need to re-evaluate the initial digits or check for errors in the input.

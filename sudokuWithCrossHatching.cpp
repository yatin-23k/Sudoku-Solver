#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

#define n 9
int grid[n][n];

// Keep track of positions and remaining count of each number in sudoku
map<int, vector<pair<int, int>>> pos;
map<int, int> rem;

// Graph to hold all possible positions for each number
map<int, map<int, vector<int>>> graph;

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
        for(int j = 0; j < 9; j++) {
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
        for(int j = 0; j < 9; j++) {
            output_file << grid[i][j] << ' ';
        }
        output_file << '\n';
    }
    output_file.close();
}

/*
 * Function to check if a number placed in a specific position is valid according to Sudoku rules.
*/
bool safeState(int row, int col) {
    int digit = grid[row][col];

    // Check if the number exists in the current row or column
    for (int i = 0; i < n; i++) {
        if (i != col && grid[row][i] == digit) return false;
        if (i != row && grid[i][col] == digit) return false;
    }

    // Check if the number exists in the current 3x3 box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (startRow + i != row && startCol + j != col && grid[startRow + i][startCol + j] == digit)
                return false;

    return true;
}

/*
 * Recursive function to solve the Sudoku problem.
 */
bool sudokuSolution(int k, vector<int> keys, int r, vector<int> rows) {
    // Loop through each possible column
    for (int c : graph[keys[k]][rows[r]]) {
        // Skip if the position is already filled
        if (grid[rows[r]][c] > 0) continue;

        // Place the number in the current position
        grid[rows[r]][c] = keys[k];

        // If it's safe, move to the next position
        if (safeState(rows[r], c)) {
            if (r < rows.size() - 1) {
                if (sudokuSolution(k, keys, r + 1, rows)) return true;
                else grid[rows[r]][c] = 0;  // Backtrack if it's not possible to fill the remaining positions
            } 
            else {
                if (k < keys.size() - 1) {
                    vector<int> nextRows;
                    for (auto &it : graph[keys[k+1]]) {
                        nextRows.push_back(it.first);
                    }
                    if (sudokuSolution(k + 1, keys, 0, nextRows)) return true;
                    else grid[rows[r]][c] = 0;  // Backtrack if it's not possible to fill the remaining positions
                } 
                else return true;   // If all positions have been filled, return true
            }
        }
        // Backtrack if the current number is not safe
        grid[rows[r]][c] = 0;
    }
    return false;   // Return false if it's not possible to fill the current position
}

/*
 * Function to build the pos and rem maps.
 * pos map keeps track of positions of each number in the grid.
 * rem map keeps track of the remaining count of each number in the grid.
*/
void buildPosAndRem() {
    // initalizing values of pos and rem
    for (int i = 1; i <= n; i++) {
        pos[i] = vector<pair<int, int>>();
        rem[i] = 9;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
             // If the cell is not empty, add its position to the map and decrement the remaining count of the number
            if (grid[i][j] > 0) {
                pos[grid[i][j]].push_back({i, j});
                rem[grid[i][j]] -= 1;
            }
        }
    }
}

/*
 * Function to build the graph which maps each number to its possible positions in the grid.
*/
void buildGraph()
{
    for (auto &it : pos)
    {
        int k = it.first;
        vector<pair<int, int>> v = it.second;
        vector<int> rows(n, 0), cols(n, 0);
        // updating the values of row and col already filled by key k
        for (auto &itr : v)
        {
            int x = itr.first, y = itr.second;
            rows[x] = 1;
            cols[y] = 1;
        }
        // For each remaining row and column, add them to the graph if the cell is empty
        for (int r = 0; r < n; r++)
        {
            if (rows[r] == 1)
                continue;
            for (int c = 0; c < n; c++)
            {
                if (cols[c] == 1)
                    continue;
                if (grid[r][c] == 0)
                    graph[k][r].push_back(c);
            }
        }
    }
}

/*
 * Function to build the keys vector, sorted on the bases of remaining elements
*/
vector<int> sortKeys() {
    vector<pair<int, int>> remVec;
    // pushing rem map key and value in remVec
    for (auto &it : rem) {
        remVec.push_back(it);
    }
    // sorting remVec by values
    sort(remVec.begin(), remVec.end(), [](pair<int, int> a, pair<int, int> b){ return a.second < b.second; });
    vector<int> keys;
    //pushing the keys from remVec to keys vector
    for (auto &it : remVec) {
        keys.push_back(it.first);
    }
    return keys;
}

int main() {
    if (!inputMatrix()) return 0;
    
    cout << "Input Sudoku:\n\n";
    printMatrix();
    
    buildPosAndRem();

    vector<int> keys = sortKeys();

    buildGraph();
    
    // building the rows vector for keys[0]
    vector<int> rows;
    for (auto &it : graph[keys[0]]) {
        rows.push_back(it.first);
    }
    
    bool solution = sudokuSolution(0, keys, 0, rows);

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

#include<bits/stdc++.h>
using namespace std;

# define n 9

void printmatrix(int sumatrix[n][n])
{
    for(int i = 0 ; i < n ; i++){
        for( int j = 0 ; j < n ; j++){

            cout << sumatrix[i][j] << "  ";
        }
        cout << "\n";
    }
}

bool safestate(int sumatrix[n][n], int row, int col, int data)
{
    for(int i = 0 ; i < n ; i++){

        if(i == row){
            continue;
        }
        if(sumatrix[i][col] == data){
            return false;
        }
    }

    for(int j = 0 ; j < n ; j++){

        if(j == col){
            continue;
        }
        if(sumatrix[row][j] == data){
            return false;
        }
    }

    int temprow = (row/3)*3;
    int tempcol = (col/3)*3;

    for(int i = temprow ; i < (temprow + 3) ; i++){
        for (int j = tempcol ; j < (tempcol + 3) ; j++){

            if(i == row && j == col){
                continue;
            }
            if(sumatrix[i][j] == data){
                return false;
            }
        }
    }

    return true;
}

bool sudokusolution(int sumatrix[n][n], int row, int col)
{
    if(row == n-1 && col == n)
        return true;
    
    if(col == n ){
        col = 0;
        row++;
    }

    if(sumatrix[row][col]!=0){
        return sudokusolution(sumatrix, row, col+1);
    }

    for(int data = 1 ; data <=n ; data++){

        if(safestate(sumatrix, row, col, data)){

            sumatrix[row][col] = data;

            if(sudokusolution(sumatrix, row, col+1))
                return true;

            sumatrix[row][col] = 0;
        }
        
    }
    return false;
}

int main()
{
    int sumatrix[n][n];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){

            cin >> sumatrix[i][j];
        }
    }

    if(sudokusolution(sumatrix, 0, 0))
        printmatrix(sumatrix);

    else
        cout << "No Solution Found" << "\n";
}


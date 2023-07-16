#include<bits/stdc++.h>
using namespace std;

# define n 9

int rowDigits[9]={0};
int colDigits[9]={0};
int boxDigits[9]={0};

int boxIndex(int x, int y)
{
    return ( (x / 3) * 3 )+ (y / 3);
}

void setInitialValue(int sumatrix[9][9])
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            
            if(sumatrix[i][j] > 0){
                rowDigits[i] |= 1 << (sumatrix[i][j] - 1);
                colDigits[j] |= 1 << (sumatrix[i][j] - 1);
                boxDigits[boxIndex(i, j)] |= 1 << (sumatrix[i][j] - 1);
            }
        }
    }
}

void printmatrix(int sumatrix[n][n])
{
    for(int i = 0 ; i < n ; i++){
        for( int j = 0 ; j < n ; j++){

            cout << sumatrix[i][j] << "  ";
        }
        cout << "\n";
    }
}

bool safestate(int sumatrix[n][n], int row, int col, int digit)
{
    if (!((boxDigits[boxIndex(row, col)] & digit) || (rowDigits[row] & digit) || (colDigits[col] & digit))){
        return true;
    }
    return false;
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

    for(int i = 1; i <= n; i++){
        int num = 1 << (i-1);
        if(safestate(sumatrix, row, col, num)){

            sumatrix[row][col] = i;
            boxDigits[boxIndex(row, col)] |= num;
            rowDigits[row] |= num;
            colDigits[col] |= num;

            if(sudokusolution(sumatrix, row, col+1))
                return true;

            sumatrix[row][col] = 0;
            boxDigits[boxIndex(row, col)] &= ~num;
            rowDigits[row] &= ~num;
            colDigits[col] &= ~num;
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

    setInitialValue(sumatrix);

    if(sudokusolution(sumatrix, 0, 0))
        printmatrix(sumatrix);

    else
        cout << "No Solution Found" << "\n";
    
    return 0;
}


#include <iostream>
#include <vector>

using namespace std;

int N;
int solutionCount = 0;

// Function to print board
void printBoard(vector<vector<int>> &board)
{
    cout << "\nSolution " << solutionCount << ":\n";

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check safe position
bool isSafe(vector<vector<int>> &board, int row, int col)
{
    int i, j;

    // Check left side row
    for(i = 0; i < col; i++)
    {
        if(board[row][i] == 1)
            return false;
    }

    // Check upper diagonal
    for(i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if(board[i][j] == 1)
            return false;
    }

    // Check lower diagonal
    for(i = row, j = col; i < N && j >= 0; i++, j--)
    {
        if(board[i][j] == 1)
            return false;
    }

    return true;
}

// Function to find all solutions
void solveNQ(vector<vector<int>> &board, int col)
{
    // All queens placed
    if(col >= N)
    {
        solutionCount++;
        printBoard(board);
        return;
    }

    // Try every row
    for(int i = 0; i < N; i++)
    {
        // Branch
        if(isSafe(board, i, col))
        {
            // Place queen
            board[i][col] = 1;

            // Recursive call
            solveNQ(board, col + 1);

            // Backtrack
            board[i][col] = 0;
        }
    }
}

int main()
{
    cout << "Enter value of N: ";
    cin >> N;

    // Create board
    vector<vector<int>> board(N, vector<int>(N, 0));

    solveNQ(board, 0);

    if(solutionCount == 0)
    {
        cout << "Solution does not exist";
    }
    else
    {
        cout << "\nTotal Solutions = " << solutionCount;
    }

    return 0;
}
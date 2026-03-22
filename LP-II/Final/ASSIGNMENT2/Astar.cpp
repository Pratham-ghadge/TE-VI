#include <iostream>
#include <vector>
using namespace std;

// 🔹 Check if safe
bool isSafe(vector<vector<int>> &board, int row, int col, int n) {
    // left row
    for (int i = 0; i < col; i++)
        if (board[row][i] == 1)
            return false;

    // upper diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;

    // lower diagonal
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j] == 1)
            return false;

    return true;
}

// 🔹 Print board
void printBoard(vector<vector<int>> &board, int n, int &count) {
    count++;
    cout << "\nSolution " << count << ":\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

// 🔹 Backtracking function
void solveNQueens(vector<vector<int>> &board, int col, int n, int &count) {
    if (col == n) {
        printBoard(board, n, count);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            board[i][col] = 1;

            solveNQueens(board, col + 1, n, count);

            board[i][col] = 0; // backtrack
        }
    }
}

// 🔹 Main
int main() {
    int n;
    cout << "Enter value of N: ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));
    int count = 0;

    solveNQueens(board, 0, n, count);

    if (count == 0)
        cout << "No solution exists\n";
    else
        cout << "\nTotal solutions: " << count << endl;

    return 0;
}
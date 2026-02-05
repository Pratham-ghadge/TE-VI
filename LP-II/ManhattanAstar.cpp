#include <bits/stdc++.h>
using namespace std;

// ===================== GLOBAL GOAL =====================
vector<vector<int>> goal(3, vector<int>(3));

// Directions: UP, DOWN, LEFT, RIGHT
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string moveName[] = {"UP", "DOWN", "LEFT", "RIGHT"};

// ===================== PRINT BOARD =====================
void printBoard(vector<vector<int>> board) {
    for (auto row : board) {
        for (int val : row) {
            if (val == 0) cout << "_ ";
            else cout << val << " ";
        }
        cout << endl;
    }
}

// ===================== MANHATTAN HEURISTIC =====================
int heuristic(vector<vector<int>> board) {
    int dist = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            int val = board[i][j];
            if (val == 0) continue;

            // Find correct position in goal
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    if (goal[x][y] == val) {
                        dist += abs(i - x) + abs(j - y);
                    }
                }
            }
        }
    }
    return dist;
}

// ===================== CREATE UNIQUE KEY =====================
string getKey(vector<vector<int>> board) {
    string key = "";
    for (auto row : board)
        for (int val : row)
            key += to_string(val);
    return key;
}

// ===================== NODE STRUCT =====================
struct Node {
    vector<vector<int>> board;
    int g, h, f;
    int blankX, blankY;
    Node* parent;

    Node(vector<vector<int>> b, int moves, int x, int y, Node* p) {
        board = b;
        g = moves;
        blankX = x;
        blankY = y;
        parent = p;

        h = heuristic(board);
        f = g + h;
    }
};

// Comparator for Priority Queue (minimum f first)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

// ===================== A* SOLVER =====================
void solveAStar(vector<vector<int>> start) {

    priority_queue<Node*, vector<Node*>, Compare> open;
    unordered_set<string> visited;

    // Find blank position in start
    int sx, sy;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (start[i][j] == 0)
                sx = i, sy = j;

    Node* startNode = new Node(start, 0, sx, sy, NULL);
    open.push(startNode);

    int stepCount = 0;

    while (!open.empty()) {

        Node* curr = open.top();
        open.pop();

        cout << "\n=====================================\n";
        cout << "STEP " << stepCount << " EXPANDING NODE\n";
        cout << "g = " << curr->g << ", h = " << curr->h
             << ", f = " << curr->f << endl;

        printBoard(curr->board);
        cout << "=====================================\n";

        stepCount++;

        // Goal reached
        if (curr->board == goal) {

            cout << "\n GOAL STATE REACHED!\n";

            // Print full path
            vector<Node*> path;
            while (curr != NULL) {
                path.push_back(curr);
                curr = curr->parent;
            }

            reverse(path.begin(), path.end());

            cout << "\n========== FINAL SOLUTION PATH ==========\n";
            for (int i = 0; i < path.size(); i++) {
                cout << "\nMove " << i << ":\n";
                cout << "g=" << path[i]->g
                     << " h=" << path[i]->h
                     << " f=" << path[i]->f << endl;

                printBoard(path[i]->board);
            }

            cout << "\nTotal Moves Required = " << path.size() - 1 << endl;
            return;
        }

        visited.insert(getKey(curr->board));

        // Expand all possible blank moves
        cout << "\nPossible Blank Moves:\n";

        for (int i = 0; i < 4; i++) {

            int nx = curr->blankX + dx[i];
            int ny = curr->blankY + dy[i];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {

                vector<vector<int>> newBoard = curr->board;
                swap(newBoard[curr->blankX][curr->blankY],
                     newBoard[nx][ny]);

                Node* child = new Node(newBoard, curr->g + 1, nx, ny, curr);

                cout << "\nMove: " << moveName[i] << endl;
                cout << "g=" << child->g
                     << " h=" << child->h
                     << " f=" << child->f << endl;

                printBoard(child->board);

                if (visited.find(getKey(newBoard)) == visited.end())
                    open.push(child);
            }
        }
    }

    cout << "\n No Solution Found!\n";
}

// ===================== MAIN FUNCTION =====================
int main() {

    vector<vector<int>> start(3, vector<int>(3));

    cout << "Enter Initial State (0 for blank):\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> start[i][j];

    cout << "\nEnter Goal State:\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> goal[i][j];

    cout << "\nSolving using A* Algorithm...\n";

    solveAStar(start);

    return 0;
}

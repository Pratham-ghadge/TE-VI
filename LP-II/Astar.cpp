#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

// Node structure
struct Node {
    int x, y;
    int g, h, f;
};

// Compare function
struct compare {
    bool operator()(Node a, Node b) {
        return a.f > b.f;
    }
};

// Heuristic Function
int heuristic(int x, int y,
              int goalX, int goalY) {

    // Manhattan Distance
    return abs(x - goalX) +
           abs(y - goalY);
}

// A* Algorithm
void astar(vector<vector<char>> grid,
           int rows, int cols,
           int startX, int startY,
           int goalX, int goalY) {

    priority_queue<Node,
                   vector<Node>,
                   compare> pq;

    // Directions
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Start Node
    Node start;

    start.x = startX;
    start.y = startY;

    start.g = 0;

    start.h = heuristic(startX,
                        startY,
                        goalX,
                        goalY);

    start.f = start.g + start.h;

    pq.push(start);

    while(!pq.empty()) {

        Node current = pq.top();
        pq.pop();

        // Print current node details
        cout << "\nVisiting Node: ("
             << current.x << ", "
             << current.y << ")"
             << endl;

        cout << "g(n) = "
             << current.g << endl;

        cout << "h(n) = "
             << current.h << endl;

        cout << "f(n) = "
             << current.f << endl;

        // Goal reached
        if(current.x == goalX &&
           current.y == goalY) {

            cout << "\nGoal Reached!"
                 << endl;

            cout << "Total Cost = "
                 << current.g
                 << endl;

            return;
        }

        // Check all 4 directions
        for(int i = 0; i < 4; i++) {

            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            // Valid cell check
            if(newX >= 0 &&
               newX < rows &&
               newY >= 0 &&
               newY < cols &&
               grid[newX][newY] != '#') {

                Node next;

                next.x = newX;
                next.y = newY;

                // Path cost
                next.g = current.g + 1;

                // Heuristic value
                next.h = heuristic(newX,
                                   newY,
                                   goalX,
                                   goalY);

                // Total cost
                next.f = next.g + next.h;

                // Print next node values
                cout << "\nPossible Move -> ("
                     << newX << ", "
                     << newY << ")"
                     << endl;

                cout << "g = "
                     << next.g
                     << ", h = "
                     << next.h
                     << ", f = "
                     << next.f
                     << endl;

                pq.push(next);
            }
        }
    }

    cout << "\nNo Path Found!"
         << endl;
}

int main() {

    int rows, cols;

    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    vector<vector<char>> grid(rows,
                              vector<char>(cols));

    cout << "\nEnter Grid:\n";
    cout << "S = Start\n";
    cout << "G = Goal\n";
    cout << "# = Block\n";
    cout << ". = Path\n\n";

    int startX, startY;
    int goalX, goalY;

    // Input Grid
    for(int i = 0; i < rows; i++) {

        for(int j = 0; j < cols; j++) {

            cin >> grid[i][j];

            // Start Position
            if(grid[i][j] == 'S') {

                startX = i;
                startY = j;
            }

            // Goal Position
            if(grid[i][j] == 'G') {

                goalX = i;
                goalY = j;
            }
        }
    }

    cout << "\nA* Traversal:\n";

    astar(grid,
          rows,
          cols,
          startX,
          startY,
          goalX,
          goalY);

    return 0;
}
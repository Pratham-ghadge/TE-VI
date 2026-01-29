#include <iostream>
#include <queue>
#include <set>
#include <cmath>
using namespace std;

/* Goal State */
int goal[3][3] = {
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}};

struct Node
{
    int mat[3][3];
    int g, h, f;
};

/* Print Matrix */
void print(int a[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

/* Manhattan Distance Heuristic */
// int heuristic(int a[3][3]) {
//     int h = 0;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             if (a[i][j] != 0) {
//                 for (int x = 0; x < 3; x++)
//                     for (int y = 0; y < 3; y++)
//                         if (goal[x][y] == a[i][j])
//                             h += abs(i - x) + abs(j - y);
//             }
//         }
//     }
//     return h;
// }

int heuristic(int a[3][3])
{
    int h = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] != 0 && a[i][j] != goal[i][j])
            {
                h++;
            }
        }
    }

    return h;
}

/* Check Goal */
bool isGoal(int a[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (a[i][j] != goal[i][j])
                return false;
    return true;
}

/* Encode state to avoid revisiting */
string encode(int a[3][3])
{
    string s = "";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            s += char(a[i][j] + '0');
    return s;
}

/* A* Algorithm with Explanation */
void AStar(int start[3][3])
{

    set<string> visited;

    Node current;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            current.mat[i][j] = start[i][j];

    current.g = 0;
    current.h = heuristic(current.mat);
    current.f = current.g + current.h;

    int step = 0;

    while (true)
    {

        cout << "\n================ STEP " << step++ << " ================\n";
        cout << "Current State:\n";
        print(current.mat);
        cout << "g = " << current.g << "  h = " << current.h
             << "  f = " << current.f << endl;

        if (isGoal(current.mat))
        {
            cout << "\n GOAL STATE REACHED\n";
            return;
        }

        visited.insert(encode(current.mat));

        int x, y;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (current.mat[i][j] == 0)
                {
                    x = i;
                    y = j;
                }

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};
        string moveName[4] = {"UP", "DOWN", "LEFT", "RIGHT"};

        Node best;
        best.f = 9999;

        cout << "\nPossible Moves:\n";

        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
            {

                Node child = current;
                swap(child.mat[x][y], child.mat[nx][ny]);

                if (visited.count(encode(child.mat)))
                    continue;

                child.g = current.g + 1;
                child.h = heuristic(child.mat);
                child.f = child.g + child.h;

                cout << "\nMove: " << moveName[k] << endl;
                print(child.mat);
                cout << "g = " << child.g
                     << "  h = " << child.h
                     << "  f = " << child.f << endl;

                if (child.f < best.f)
                {
                    best = child;
                }
            }
        }

        cout << "\nSelected Move (Minimum f):\n";
        print(best.mat);
        cout << "f = " << best.f << endl;

        current = best;
    }
}

int main()
{

    int start[3][3] = {
        {1, 2, 3},
        {8, 4, 5},
        {7, 6, 0}};

    AStar(start);
    return 0;
}

/*   OUTPUT

================ STEP 0 ================
Current State:
1 2 3
8 4 5
7 6 0
g = 0  h = 2  f = 2

Possible Moves:

Move: UP
1 2 3
8 4 0
7 6 5
g = 1  h = 1  f = 2

Move: LEFT
1 2 3
8 4 5
7 0 6
g = 1  h = 3  f = 4

Selected Move (Minimum f):
1 2 3
8 4 0
7 6 5
f = 2

================ STEP 1 ================
Current State:
1 2 3
8 4 0
7 6 5
g = 1  h = 1  f = 2

Possible Moves:

Move: UP
1 2 0
8 4 3
7 6 5
g = 2  h = 2  f = 4

Move: LEFT
1 2 3
8 0 4
7 6 5
g = 2  h = 0  f = 2

Selected Move (Minimum f):
1 2 3
8 0 4
7 6 5
f = 2

================ STEP 2 ================
Current State:
1 2 3
8 0 4
7 6 5
g = 2  h = 0  f = 2

GOAL STATE REACHED

*/
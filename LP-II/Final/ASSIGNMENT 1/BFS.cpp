#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 🔹 Function to take input
void addFriendships(vector<vector<int>> &adj, int m) {
    cout << "Enter friendships (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

// 🔹 BFS function to calculate friend levels
vector<int> bfsLevels(vector<vector<int>> &adj, int start) {
    int n = adj.size();
    vector<int> level(n, -1);
    queue<int> q;

    level[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            if (level[neighbor] == -1) {
                level[neighbor] = level[node] + 1;
                q.push(neighbor);
            }
        }
    }

    return level;
}

// 🔹 Function to print result
void printLevels(vector<int> &level) {
    cout << "\nFriend Levels:\n";
    for (int i = 0; i < level.size(); i++) {
        cout << "Person " << i << " -> Level " << level[i] << endl;
    }
}

// 🔹 Main function
int main() {
    int n, m;

    cout << "Enter number of people: ";
    cin >> n;

    vector<vector<int>> adj(n);

    cout << "Enter number of friendships: ";
    cin >> m;

    addFriendships(adj, m);

    int start;
    cout << "Enter starting person: ";
    cin >> start;

    vector<int> result = bfsLevels(adj, start);

    printLevels(result);

    return 0;
}


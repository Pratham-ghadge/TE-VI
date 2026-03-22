#include <iostream>
#include <vector>
using namespace std;

// 🔹 DFS function
void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            cout << node << " -> " << neighbor << endl;

            dfs(neighbor, adj, visited);

            cout << "Back to " << node << endl;
        }
    }
}

// 🔹 Function to take input
void addEdges(vector<vector<int>> &adj, int e) {
    cout << "Enter edges (from to):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // directed graph
    }
}

// 🔹 Main
int main() {
    int n, e;

    cout << "Enter number of nodes: ";
    cin >> n;

    vector<vector<int>> adj(n);

    cout << "Enter number of edges: ";
    cin >> e;

    addEdges(adj, e);

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    vector<bool> visited(n, false);

    cout << "\nDFS with Backtracking:\n";
    dfs(start, adj, visited);

    return 0;
}





// #include <iostream>
// #include <map>
// #include <vector>
// using namespace std;

// // 🔹 DFS function
// void dfs(string node, map<string, vector<string>> &adj, map<string, bool> &visited) {
//     visited[node] = true;

//     for (string neighbor : adj[node]) {
//         if (!visited[neighbor]) {
//             cout << node << " -> " << neighbor << endl;

//             dfs(neighbor, adj, visited);

//             cout << "Back to " << node << endl;
//         }
//     }
// }

// // 🔹 Function to add connections
// void addEdges(map<string, vector<string>> &adj, int e) {
//     cout << "Enter connections (from to):\n";
//     for (int i = 0; i < e; i++) {
//         string u, v;
//         cin >> u >> v;

//         adj[u].push_back(v);
//         adj[v]; // ensure node exists
//     }
// }

// // 🔹 Main
// int main() {
//     int e;

//     map<string, vector<string>> adj;
//     map<string, bool> visited;

//     cout << "Enter number of connections: ";
//     cin >> e;

//     addEdges(adj, e);

//     string start;
//     cout << "Enter starting file/folder: ";
//     cin >> start;

//     // initialize visited
//     for (auto &pair : adj) {
//         visited[pair.first] = false;
//     }

//     cout << "\nDFS File Traversal:\n";
//     dfs(start, adj, visited);

//     return 0;
// }
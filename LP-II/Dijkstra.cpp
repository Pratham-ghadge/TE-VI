#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define MAX 100

int main() {
    int n, e;

    cout << "Enter number of locations: ";
    cin >> n;

    cout << "Enter number of roads: ";
    cin >> e;

    vector<pair<int,int>> adj[MAX];

    cout << "Enter roads (source destination time):\n";
    for(int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // because roads are two-way
    }

    int source = 0; // Hospital fixed as 0
    int destination;

    cout << "Enter accident location: ";
    cin >> destination;

    int dist[MAX], visited[MAX], parent[MAX];

    for(int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    // Dijkstra Algorithm
    for(int i = 0; i < n-1; i++) {
        int min = INT_MAX, u;

        for(int j = 0; j < n; j++) {
            if(!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        visited[u] = 1;

        for(auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if(!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    cout << "\nMinimum travel time = " << dist[destination] << " minutes\n";

    cout << "Route: ";
    int temp = destination;
    while(temp != -1) {
        cout << temp;
        if(parent[temp] != -1)
            cout << " <- ";
        temp = parent[temp];
    }

    return 0;
}
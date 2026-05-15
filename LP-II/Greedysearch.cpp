#include<iostream>
#include<algorithm>
#include<climits>

using namespace std;

//////////////////////////////////////////////////////
// Selection Sort
//////////////////////////////////////////////////////

void selectionSort()
{
    int n, a[20];

    cout << "\n--- Selection Sort ---\n";

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // Sorting
    for(int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for(int j = i + 1; j < n; j++)
        {
            if(a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }

        swap(a[i], a[minIndex]);
    }

    cout << "\nSorted Elements:\n";

    for(int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }

    cout << endl;
}

//////////////////////////////////////////////////////
// Job Scheduling
//////////////////////////////////////////////////////

struct Job
{
    int id, deadline, profit;
};

bool compare(Job a, Job b)
{
    return a.profit > b.profit;
}

void jobScheduling()
{
    int n;

    cout << "\n--- Job Scheduling ---\n";

    cout << "Enter number of jobs: ";
    cin >> n;

    Job job[20];

    for(int i = 0; i < n; i++)
    {
        job[i].id = i + 1;

        cout << "Enter deadline for Job "
             << i + 1 << ": ";
        cin >> job[i].deadline;

        cout << "Enter profit for Job "
             << i + 1 << ": ";
        cin >> job[i].profit;
    }

    // Sort by profit
    sort(job, job + n, compare);

    int slot[20] = {0};

    int totalProfit = 0;

    cout << "\nSelected Jobs:\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = job[i].deadline - 1; j >= 0; j--)
        {
            if(slot[j] == 0)
            {
                slot[j] = 1;

                cout << "Job "
                     << job[i].id
                     << " ";

                totalProfit += job[i].profit;

                break;
            }
        }
    }

    cout << "\nTotal Profit = "
         << totalProfit << endl;
}

//////////////////////////////////////////////////////
// Dijkstra Algorithm
//////////////////////////////////////////////////////

void dijkstra()
{
    int n, e;

    cout << "\n--- Dijkstra Algorithm ---\n";

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    int cost[20][20];

    // Initialize matrix
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                cost[i][j] = 0;
            else
                cost[i][j] = 999;
        }
    }

    cout << "\nEnter source destination weight:\n";

    for(int i = 0; i < e; i++)
    {
        int u, v, w;

        cin >> u >> v >> w;

        cost[u][v] = w;
        cost[v][u] = w; // Undirected graph
    }

    int source;

    cout << "Enter source vertex: ";
    cin >> source;

    int dist[20], visited[20];

    for(int i = 0; i < n; i++)
    {
        dist[i] = cost[source][i];
        visited[i] = 0;
    }

    dist[source] = 0;
    visited[source] = 1;

    for(int count = 0; count < n - 1; count++)
    {
        int min = 999;
        int u;

        for(int i = 0; i < n; i++)
        {
            if(!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        for(int v = 0; v < n; v++)
        {
            if(!visited[v] &&
               dist[u] + cost[u][v] < dist[v])
            {
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }

    cout << "\nShortest Distances:\n";

    for(int i = 0; i < n; i++)
    {
        cout << "Vertex "
             << i
             << " = "
             << dist[i] << endl;
    }
}

//////////////////////////////////////////////////////
// Prim's Algorithm
//////////////////////////////////////////////////////

void prims()
{
    int n;

    cout << "\n--- Prim's Algorithm ---\n";

    cout << "Enter number of vertices: ";
    cin >> n;

    int graph[20][20];

    cout << "Enter adjacency matrix:\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    bool visited[20] = {false};

    visited[0] = true;

    int edges = 0;
    int totalCost = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    while(edges < n - 1)
    {
        int min = INT_MAX;
        int x = 0, y = 0;

        for(int i = 0; i < n; i++)
        {
            if(visited[i])
            {
                for(int j = 0; j < n; j++)
                {
                    if(!visited[j] &&
                       graph[i][j] != 0)
                    {
                        if(graph[i][j] < min)
                        {
                            min = graph[i][j];

                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        cout << x
             << " - "
             << y
             << " = "
             << graph[x][y]
             << endl;

        totalCost += graph[x][y];

        visited[y] = true;

        edges++;
    }

    cout << "\nTotal Cost = "
         << totalCost << endl;
}

//////////////////////////////////////////////////////
// Main Function
//////////////////////////////////////////////////////

int main()
{
    int choice;

    do
    {
        cout << "\n========== MENU ==========\n";

        cout << "1. Selection Sort\n";
        cout << "2. Job Scheduling\n";
        cout << "3. Dijkstra Algorithm\n";
        cout << "4. Prim's Algorithm\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                selectionSort();
                break;

            case 2:
                jobScheduling();
                break;

            case 3:
                dijkstra();
                break;

            case 4:
                prims();
                break;

            case 5:
                cout << "\nProgram Ended\n";
                break;

            default:
                cout << "\nInvalid Choice\n";
        }

    } while(choice != 5);

    return 0;
}
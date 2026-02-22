#include <iostream>
#include <climits>
using namespace std;

#define MAX 100

int main() {
    int n;
    cout << "Enter number of buildings: ";
    cin >> n;

    int cost[MAX][MAX];

    cout << "Enter pipe installation cost matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    int selected[MAX];     // Track selected buildings
    int minCost = 0;
    
    for(int i = 0; i < n; i++)
        selected[i] = 0;

    selected[0] = 1;  // Start from building 1

    cout << "\nPipelines selected:\n";

    for(int edge = 0; edge < n-1; edge++) {

        int min = INT_MAX;
        int x = 0, y = 0;

        for(int i = 0; i < n; i++) {
            if(selected[i]) {
                for(int j = 0; j < n; j++) {
                    if(!selected[j] && cost[i][j]) {
                        if(cost[i][j] < min) {
                            min = cost[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        cout << "Building " << x+1 << " - Building " << y+1
             << "  Cost: " << cost[x][y] << endl;

        minCost += cost[x][y];
        selected[y] = 1;
    }

    cout << "\nMinimum Total Pipeline Cost = " << minCost << endl;

    return 0;
}
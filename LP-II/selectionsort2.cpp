#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter number of routers: ";
    cin >> n;

    int distance[n];

    cout << "Enter distance from Device to each Router:\n";
    for(int i = 0; i < n; i++) {
        cout << "Distance to Router " << i+1 << ": ";
        cin >> distance[i];
    }

    // Selection Sort
    for(int i = 0; i < n-1; i++) {
        int minIndex = i;

        for(int j = i+1; j < n; j++) {
            if(distance[j] < distance[minIndex]) {
                minIndex = j;
            }
        }

        // Swap
        int temp = distance[i];
        distance[i] = distance[minIndex];
        distance[minIndex] = temp;
    }

    cout << "\nSorted Distances:\n";
    for(int i = 0; i < n; i++) {
        cout << distance[i] << " ";
    }

    cout << "\n\nNearest Router Distance: " << distance[0];

    return 0;
}
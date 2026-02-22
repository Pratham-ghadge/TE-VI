#include <iostream>
#include <cmath>
using namespace std;

struct Router {
    int id;
    double x, y;
    double distance;
};

int main() {
    int n;
    cout << "Enter number of routers: ";
    cin >> n;

    Router routers[n];

    double deviceX, deviceY;
    cout << "Enter device coordinates (x y): ";
    cin >> deviceX >> deviceY;

    // Input router coordinates
    for(int i = 0; i < n; i++) {
        cout << "Enter coordinates of Router " << i+1 << " (x y): ";
        cin >> routers[i].x >> routers[i].y;
        routers[i].id = i+1;

        // Calculate distance from device
        routers[i].distance = sqrt(
            pow(routers[i].x - deviceX, 2) +
            pow(routers[i].y - deviceY, 2)
        );
    }

    // Selection Sort based on distance
    for(int i = 0; i < n-1; i++) {
        int minIndex = i;
        for(int j = i+1; j < n; j++) {
            if(routers[j].distance < routers[minIndex].distance) {
                minIndex = j;
            }
        }

        // Swap
        Router temp = routers[i];
        routers[i] = routers[minIndex];
        routers[minIndex] = temp;
    }

    cout << "\nRouters sorted by distance:\n";
    for(int i = 0; i < n; i++) {
        cout << "Router " << routers[i].id
             << " Distance: " << routers[i].distance << endl;
    }

    cout << "\nDevice will connect to Router "
         << routers[0].id
         << " (Nearest Router)" << endl;

    return 0;
}
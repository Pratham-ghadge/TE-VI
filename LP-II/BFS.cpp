#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <climits>

using namespace std;

class WifiRouterPlacement {
private:
    map<string, vector<string>> graph;

    // BFS-2: Calculate distance (signal strength) from router room
    map<string, int> bfsSignalStrength(const string& start) {
        map<string, int> distance;
        queue<string> q;

        for (auto& pair : graph) {
            distance[pair.first] = -1;
        }

        distance[start] = 0;
        q.push(start);

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            for (const string& neighbor : graph[current]) {
                if (distance[neighbor] == -1) {
                    distance[neighbor] = distance[current] + 1;
                    q.push(neighbor);
                }
            }
        }
        return distance;
    }

public:
    void addRoom(const string& room) {
        graph[room];
    }

    void addConnection(const string& a, const string& b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    void findOptimalRouter() {
        string bestRoom;
        int bestMaxDistance = INT_MAX;

        cout << "\nBFS-1: Trying each room as router location\n";

        // BFS-1: Try each room
        for (auto& pair : graph) {
            string room = pair.first;

            cout << "\nPlacing router in room: " << room << endl;

            // BFS-2: Calculate signal strength
            map<string, int> distance = bfsSignalStrength(room);

            int maxDistance = 0;
            bool validPlacement = true;

            cout << "Signal strength from room " << room << ":\n";

            for (auto& d : distance) {
                cout << "Room " << d.first << " -> Distance: " << d.second;

                if (d.second == 0)
                    cout << " (Excellent)";
                else if (d.second == 1)
                    cout << " (Strong)";
                else if (d.second == 2)
                    cout << " (Good)";
                else {
                    cout << " (Weak)";
                    validPlacement = false;
                }

                cout << endl;
                maxDistance = max(maxDistance, d.second);
            }

            if (validPlacement) {
                cout << "Placement VALID\n";
                if (maxDistance < bestMaxDistance) {
                    bestMaxDistance = maxDistance;
                    bestRoom = room;
                }
            } else {
                cout << "Placement INVALID (weak signal exists)\n";
            }
        }

        cout << "\nFINAL RESULT\n";
        if (bestRoom.empty()) {
            cout << "No valid router placement found.\n";
        } else {
            cout << "Best room to place router: " << bestRoom << endl;
            cout << "Maximum distance to any room: " << bestMaxDistance << endl;
        }
    }
};

int main() {
    WifiRouterPlacement wifi;
    int choice;

    while (true) {
        cout << "\nMENU\n";
        cout << "1. Add room\n";
        cout << "2. Add connection\n";
        cout << "3. Find optimal router placement\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string room;
            cout << "Enter room name: ";
            cin.ignore();
            getline(cin, room);
            wifi.addRoom(room);
        }
        else if (choice == 2) {
            string a, b;
            cout << "Enter first room: ";
            cin.ignore();
            getline(cin, a);
            cout << "Enter second room: ";
            getline(cin, b);
            wifi.addConnection(a, b);
        }
        else if (choice == 3) {
            wifi.findOptimalRouter();
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}

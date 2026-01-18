#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class PipelineLeakDetector {
private:
    // Directed graph: sector -> downstream sectors
    map<string, vector<string>> graph;

    // DFS tracking
    map<string, bool> visited;
    vector<string> affectedSectors;

    // Recursive DFS
    void dfs(const string& sector) {
        visited[sector] = true;
        affectedSectors.push_back(sector);

        for (const string& nextSector : graph[sector]) {
            if (!visited[nextSector]) {
                dfs(nextSector);
            }
        }
    }

public:
    void addSector(const string& name) {
        graph[name];  // Initialize sector in graph
        visited[name] = false;
    }

    void addConnection(const string& from, const string& to) {
        if (graph.find(from) == graph.end() || graph.find(to) == graph.end()) {
            cout << "Invalid sector name." << endl;
            return;
        }
        graph[from].push_back(to);
        cout << "Pipeline added from " << from << " to " << to << endl;
    }

    void analyzeLeak(const vector<string>& leakSectors) {
        // Reset visited
        for (auto& pair : visited) {
            pair.second = false;
        }
        affectedSectors.clear();

        // Run DFS from each leak sector
        for (const string& leak : leakSectors) {
            if (graph.find(leak) != graph.end() && !visited[leak]) {
                cout << "\nLeak detected at sector: " << leak << endl;
                dfs(leak);
            }
        }

        // Display result
        cout << "\nAffected Sectors:" << endl;
        if (affectedSectors.empty()) {
            cout << "No sectors are affected." << endl;
        } else {
            for (const string& sec : affectedSectors) {
                cout << sec << endl;
            }
        }

        cout << "\nSafe Sectors:" << endl;
        bool safeFound = false;
        for (const auto& pair : graph) {
            if (!visited[pair.first]) {
                cout << pair.first << endl;
                safeFound = true;
            }
        }
        if (!safeFound) {
            cout << "No safe sectors." << endl;
        }
    }

    void displayNetwork() {
        cout << "\nPipeline Network:" << endl;
        for (const auto& pair : graph) {
            cout << pair.first << " -> ";
            for (const string& next : pair.second) {
                cout << next << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    PipelineLeakDetector network;
    int choice;

    while (true) {
        cout << "\nMENU" << endl;
        cout << "1. Add Sector" << endl;
        cout << "2. Add Pipeline Connection" << endl;
        cout << "3. Display Network" << endl;
        cout << "4. Analyze Leak using DFS" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string sector;
            cout << "Enter sector name: ";
            cin.ignore();
            getline(cin, sector);
            network.addSector(sector);
        }
        else if (choice == 2) {
            string from, to;
            cout << "Enter source sector: ";
            cin.ignore();
            getline(cin, from);
            cout << "Enter destination sector: ";
            getline(cin, to);
            network.addConnection(from, to);
        }
        else if (choice == 3) {
            network.displayNetwork();
        }
        else if (choice == 4) {
            int n;
            cout << "Enter number of leak sectors: ";
            cin >> n;
            vector<string> leaks(n);

            cin.ignore();
            for (int i = 0; i < n; i++) {
                cout << "Enter leak sector " << i + 1 << ": ";
                getline(cin, leaks[i]);
            }

            network.analyzeLeak(leaks);
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}

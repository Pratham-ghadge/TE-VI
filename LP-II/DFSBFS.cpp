
     #include <iostream>
#include <vector>
#include <queue>

using namespace std;

class SocialNetwork
{
    int users;
    vector<vector<int>> friends;

public:

    // Constructor
    SocialNetwork(int u)
    {
        users = u;
        friends.resize(u);
    }

    // Add friendship connection
    void addFriend(int u, int v)
    {
        friends[u].push_back(v);
        friends[v].push_back(u);
    }

    // Recursive DFS
    void DFS(int user, vector<bool> &visited)
    {
        visited[user] = true;

        cout << "User " << user << " ";

        for (int friendUser : friends[user])
        {
            if (!visited[friendUser])
            {
                DFS(friendUser, visited);
            }
        }
    }

    // BFS
    void BFS(int startUser)
    {
        vector<bool> visited(users, false);
        queue<int> q;

        visited[startUser] = true;
        q.push(startUser);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            cout << "User " << current << " ";

            for (int friendUser : friends[current])
            {
                if (!visited[friendUser])
                {
                    visited[friendUser] = true;
                    q.push(friendUser);
                }
            }
        }
    }
};

int main()
{
    int users, connections;

    cout << "Enter number of users: ";
    cin >> users;

    cout << "Enter number of friendship connections: ";
    cin >> connections;

    SocialNetwork sn(users);

    cout << "Enter friendship connections:" << endl;

    for (int i = 0; i < connections; i++)
    {
        int u, v;
        cin >> u >> v;

        sn.addFriend(u, v);
    }

    int start;

    cout << "Enter starting user: ";
    cin >> start;

    // DFS
    vector<bool> visited(users, false);

    cout << "\nDFS Friend Traversal:" << endl;
    sn.DFS(start, visited);

    // BFS
    cout << "\n\nBFS Friend Traversal:" << endl;
    sn.BFS(start);

    return 0;
}
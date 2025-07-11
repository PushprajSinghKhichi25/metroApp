#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <stack>

using namespace std;

// Alias for readability
typedef pair<int, string> Edge; // (weight, destination)

class MetroGraph {
private:
    unordered_map<string, vector<Edge>> adjList;
    const int baseFare = 10;     // Flat fare
    const int ratePerKm = 2;     // Fare per distance unit

public:
    // Add a connection between stations
    void addEdge(const string& u, const string& v, int weight) {
        adjList[u].push_back({weight, v});
        adjList[v].push_back({weight, u}); // Undirected graph
    }

    // Dijkstra's algorithm to find shortest path and fare
    void shortestPath(const string& source, const string& destination) {
        unordered_map<string, int> distance;
        unordered_map<string, string> previous;
        for (auto& pair : adjList) {
            distance[pair.first] = INT_MAX;
        }

        distance[source] = 0;

        // Min-heap priority queue: (distance, station)
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> minHeap;
        minHeap.push({0, source});

        while (!minHeap.empty()) {
            auto [dist, current] = minHeap.top();
            minHeap.pop();

            if (current == destination) break;

            for (auto& [weight, neighbor] : adjList[current]) {
                if (distance[neighbor] > distance[current] + weight) {
                    distance[neighbor] = distance[current] + weight;
                    previous[neighbor] = current;
                    minHeap.push({distance[neighbor], neighbor});
                }
            }
        }

        // If destination not reachable
        if (distance[destination] == INT_MAX) {
            cout << "No path exists from " << source << " to " << destination << ".\n";
            return;
        }

        // Reconstruct path
        stack<string> pathStack;
        string current = destination;
        while (current != source) {
            pathStack.push(current);
            current = previous[current];
        }
        pathStack.push(source);

        // Output
        cout << "Shortest path from " << source << " to " << destination << ":\n";
        while (!pathStack.empty()) {
            cout << pathStack.top();
            pathStack.pop();
            if (!pathStack.empty()) cout << " -> ";
        }
        cout << "\n";

        cout << "Total distance: " << distance[destination] << "\n";

        int totalFare = baseFare + ratePerKm * distance[destination];
        cout << "Minimum fare: Rs." << totalFare << "\n";
    }
};

int main() {
    MetroGraph metro;
    /*
           [Begumpet]
         /     \
        6       7
      /           \
[Ameerpet]--5--[Punjagutta]--3--[Irrum Manzil]
     |  \             |              |
     |   \            |              4
     4    6           4              |
     |     \          |           [Khairatabad]
[Prakash Nagar]       |               |
     |                |               6
     5                |               |
[Rasoolpura]       [Lakdikapul]--5--[Assembly]
   */

metro.addEdge("Ameerpet", "Punjagutta", 5);
metro.addEdge("Punjagutta", "Irrum Manzil", 3);
metro.addEdge("Punjagutta", "Khairatabad", 4);
metro.addEdge("Khairatabad", "Lakdikapul", 6);
metro.addEdge("Lakdikapul", "Assembly", 5);

metro.addEdge("Ameerpet", "Begumpet", 6);
metro.addEdge("Begumpet", "Prakash Nagar", 7);
metro.addEdge("Prakash Nagar", "Rasoolpura", 5);

metro.addEdge("Khairatabad", "Lakdikapul", 6);

    string source, destination;
    cout << "Enter source station: ";
    cin >> source;
    cout << "Enter destination station: ";
    cin >> destination;

    metro.shortestPath(source, destination);

    return 0;
}

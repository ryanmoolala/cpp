#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
#include <random>
#include <algorithm>

using namespace std;

using Graph = vector<vector<tuple<int, int>>>;

void addEdge(Graph& graph, int source, int destination, int weight) {
    graph[source].push_back(make_tuple(destination, weight));
}

Graph createGraph(int size) {
    Graph graph(size);

    // Set up RNG
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);        // weight
    std::uniform_int_distribution<> node(0, size - 1);   // node index

    // ✅ Guarantee at least one path from 0 to size-1
    vector<int> path;
    for (int i = 1; i < size - 1; ++i) {
        path.push_back(i);
    }
    std::shuffle(path.begin(), path.end(), gen);

    int prev = 0;
    for (int i = 0; i < path.size(); ++i) {
        addEdge(graph, prev, path[i], dist(gen));
        prev = path[i];
    }
    addEdge(graph, prev, size - 1, dist(gen));

    // ✅ Add random edges (excluding self-loops)
    int totalEdges = static_cast<int>(size * (size - 1) * 0.75);
    for (int i = 0; i < totalEdges; i++) {
        int u = node(gen);
        int v = node(gen);
        int weight = dist(gen);
        if (u != v) {
            addEdge(graph, u, v, weight);
        }
    }

    return graph;
}

int dijkstra(Graph& graph, int size, int end) {
    const int INF = std::numeric_limits<int>::max();
    vector<int> distances(size, INF);
    using T = pair<int, int>; // (distance, node)
    priority_queue<T, vector<T>, greater<T>> minHeap;

    distances[0] = 0;
    minHeap.push({0, 0});

    while (!minHeap.empty()) {
        auto [currDist, nodeIdx] = minHeap.top();
        minHeap.pop();

        if (nodeIdx == end) {
            return currDist;
        }

        for (auto& [neighbourIdx, weight] : graph[nodeIdx]) {
            int newDist = currDist + weight;
            if (newDist < distances[neighbourIdx]) {
                distances[neighbourIdx] = newDist;
                minHeap.push({newDist, neighbourIdx});
            }
        }
    }

    return -1; // No path found
}

int main() {
    vector<Graph> graphArray;
    vector<int> shortestPaths;

    int nodes = 10;
    for (int i = 0; i < 5; i++) {
        graphArray.push_back(createGraph(nodes));
        nodes += 10;
    }

    for (Graph& g : graphArray) {
        int shortest_path = dijkstra(g, g.size(), g.size() - 1);
        shortestPaths.push_back(shortest_path);
    }

    cout << "Shortest paths:\n";
    for (int path : shortestPaths) {
        cout << path << " ";
    }
    cout << endl;

    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> createDAG() {
    vector<vector<int>> graph(8);
    graph[0] = {1, 2};      // 0 -> 1, 0 -> 2
    graph[1] = {3};         // 1 -> 3
    graph[2] = {3, 4};      // 2 -> 3, 2 -> 4
    graph[3] = {5};         // 3 -> 5
    graph[4] = {5, 6};      // 4 -> 5, 4 -> 6
    graph[5] = {7};         // 5 -> 7
    graph[6] = {7};         // 6 -> 7
    graph[7] = {};  
    return graph;
}

void dfs_toposort(int node, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& stack) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs_toposort(neighbor, graph, visited, stack);
        }
    }
    stack.push_back(node);
}

vector<int> topological_sort(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> stack;
    for (int node = 0; node < n; ++node) {
        if (!visited[node]) {
            dfs_toposort(node, graph, visited, stack);
        }
    }
    reverse(stack.begin(), stack.end());
    return stack;
}

int main() {
    vector<vector<int>> graph = createDAG();
    vector<int> topo_order = topological_sort(graph);
    cout << "Topological order: ";
    for (int node : topo_order) {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}
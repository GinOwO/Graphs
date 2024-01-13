#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 2642 - Design Graph with Shortest Path Calculator
        Design a graph with a shortest path calculator.
        The graph is represented by a list of edges.
        The shortest path calculator calculates the shortest path from node1 to node2.
        If there is no path from node1 to node2, return -1.

        Simple Dijkstra implementation.

        Time complexity: O(ElogV), Space complexity: O(n)
            where E is the number of edges.
*/

class Graph {
    vector<vector<pair<int, int>>> adj;
public:
    Graph(int n, vector<vector<int>>& edges) :adj(n) {
        for ( auto& v : edges ) addEdge(v);
    }

    inline void addEdge(const vector<int>& edge) {
        adj[edge[0]].push_back({ edge[1], edge[2] });
    }

    int shortestPath(int node1, int node2) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({ 0,node1 });

        vector<int> dist(adj.size(), INT_MAX);
        dist[node1] = 0;

        while ( !q.empty() ) {
            auto [x, y] = q.top(); q.pop();
            if ( y == node2 ) return x;
            if ( x > dist[y] ) continue;

            for ( auto& [a, b] : adj[y] ) {
                if ( x + b < dist[a] ) {
                    dist[a] = x + b;
                    q.push({ x + b,a });
                }
            }
        }
        return -1;
    }
};

int main() {
    int n = 5;
    vector<vector<int>> edges = { {0,1,10},{0,2,3},{1,2,1},{1,3,2},{2,1,4},{2,3,8},{2,4,2},{3,4,7},{4,3,9} };
    Graph g(n, edges);
    cout << g.shortestPath(0, 4);
}
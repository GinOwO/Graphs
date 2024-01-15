#include <bits/stdc++.h>

using namespace std;

/*
    LeetCode 1192. Critical Connections in a Network
        Given an underected connected graph with n nodes labeled 1..n. A bridge (cut edge) is defined as an edge which,
        when removed, makes the graph disconnected (or more precisely, increases the number of connected components in the graph).
        Find all the bridges in the given graph. Output the bridges in any order.

        We use Tarjan's algorithm to find bridges in a graph.
        We have a timer that keeps track of the order in which we visit nodes for the first time and
            a low array that keeps track of the lowest order node that we can reach from the current node.
        If the low value of a child node is greater than the order of the current node, then the edge connecting
            the current node and the child node is a bridge.
        We use a visited array to keep track of the nodes that we have visited.
        We do not update the low value of a node if the child node is the parent node.

        Time: O(V + E), Space: O(V + E)
*/

class Solution {
    int timer = 1;
public:
    void dfs(int node, int parent, vector<int>& order, vector<int>& low,
        vector<bool>& visited, vector<vector<int>>& bridges, const vector<vector<int>>& graph) {
        visited[node] = 1;
        order[node] = low[node] = timer++;

        for ( auto& c : graph[node] ) {
            if ( c == parent ) continue;
            if ( !visited[c] ) {
                dfs(c, node, order, low, visited, bridges, graph);
                if ( low[c] > order[node] ) {
                    bridges.push_back({ c, node });
                }
            }
            low[node] = min(low[c], low[node]);
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> graph(n), bridges;
        vector<int> order(n, 0), low(n, 0);
        vector<bool> visited(n, 0);

        for ( auto& edge : connections ) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        dfs(0, -1, order, low, visited, bridges, graph);
        return bridges;
    }
};

int main() {
    Solution s;
    vector<vector<int>> connections { {0,1},{1,2},{2,0},{1,3} };
    int n = 4;
    vector<vector<int>> bridges = s.criticalConnections(n, connections);
    for ( auto& bridge : bridges ) {
        cout << bridge[0] << " " << bridge[1] << endl;
    }
    return 0;
}
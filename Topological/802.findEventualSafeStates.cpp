#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 802 - Find Eventual Safe States
        Given a directed graph, return all the vertices that are not part of a cycle.
        A vertex is part of a cycle if we can reach it from itself.
        A vertex is not part of a cycle if we can't reach it from itself.

        We do a DFS from all the unvisited vertices. We now check if its safe by doing a DFS from all the vertices that are reachable from it.
        If we encounter a vertex that is already visited, then we check if it is part of the current path. If it is, then the vertex is not safe.
        Else, we continue.

        Finally set the vertex as safe and unset it as part of the current path.

        Once all the vertices are visited, we return all the vertices that are safe.

        Time: O(n+m), Space: O(n)
*/

class Solution {
    bool dfs(const vector<vector<int>>& graph, int i,
        vector<bool>& visited, vector<bool>& path, vector<bool>& safe) {

        path[i] = visited[i] = 1;

        for ( auto& v : graph[i] ) {
            if ( visited[v] && safe[v] ) continue;
            else if ( !visited[v] ) {
                if ( dfs(graph, v, visited, path, safe) ) return true;
            }
            else if ( path[v] ) {
                return true;
            }
        }

        path[i] = 0;
        safe[i] = 1;
        return false;
    }

public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<bool> safe(n, 0), visited(n, 0), path(n, 0);
        vector<int> ans;

        for ( int i = 0; i < n; i++ ) {
            if ( visited[i] == 0 ) {
                dfs(graph, i, visited, path, safe);
            }
        }

        for ( int i = 0; i < n; i++ ) {
            if ( safe[i] ) ans.push_back(i);
        }

        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> graph = { {1,2},{2,3},{5},{0},{5},{},{} };
    vector<int> ans = s.eventualSafeNodes(graph);
    for ( auto& x : ans ) cout << x << " ";
    cout << endl;
    return 0;
}


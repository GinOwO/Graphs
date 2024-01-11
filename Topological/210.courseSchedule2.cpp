#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 210 - Course Schedule 2
        Given a directed graph, return the topological sort of the graph.
        If the graph has a cycle, return an empty array.

        We do a topological sort using kahn algo of the graph.
        If there exists a cycle, i.e size of resultant != number of vertices, return empty vector
        Else, return the reverse of the topological sort
            Or if we were to reverse the edges while making the adj list, we can return the topological sort as it is.
            Since it basically does the same thing

        Time: O(n+m), Space: O(n)
*/

class Solution {
public:
    vector<int> kahnTopoSort(int n, const vector<vector<int>>& graph) {
        vector<int> inDegree(n, 0), ans;
        queue<int> que;

        for ( int i = 0; i < n; i++ ) {
            for ( auto& v : graph[i] ) inDegree[v]++;
        }

        for ( int i = 0; i < n; i++ ) {
            if ( !inDegree[i] ) que.push(i);
        }

        while ( !que.empty() ) {
            int curr = que.front();
            que.pop();
            ans.push_back(curr);

            for ( auto& v : graph[curr] ) {
                if ( --inDegree[v] == 0 ) que.push(v);
            }
        }
        if ( ans.size() != n ) return {};
        return ans;
    }

    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(n, vector<int>{});
        for ( auto& a : prerequisites ) {
            graph[a[1]].push_back(a[0]);
        }
        return kahnTopoSort(n, graph);
    }
};

int main() {
    Solution s;
    vector<vector<int>> prerequisites { {1,0},{0,1} };
    vector<int> ans = s.findOrder(2, prerequisites);
    for ( auto& a : ans ) cout << a << " ";
    cout << endl;
    return 0;
}
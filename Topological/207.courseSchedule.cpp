#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 207 - Course Schedule
        Given a directed graph, return true if it is a DAG, else false.
        A graph is a DAG if it has no cycles.

        We do a topological sort using kahn algo of the graph.
        Return true if the size of the topological sort is equal to the number of vertices (i.e no cycles)
        Else, return false (i.e there is a cycle)

        Time: O(n+m), Space: O(n)

*/

class Solution {
public:
    bool detectCycles(const vector<vector<int>>& graph) {
        int n = graph.size();
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

        return ans.size() == n;
    }

    bool canFinish(int n, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(n, vector<int>{});
        for ( auto& a : prerequisites ) {
            graph[a[0]].push_back(a[1]);
        }
        return detectCycles(graph);
    }
};

int main() {
    Solution s;
    vector<vector<int>> prerequisites { {1,0},{0,1} };
    cout << s.canFinish(2, prerequisites) << endl;
    return 0;
}
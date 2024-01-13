#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 1976 - Number of Ways to Arrive at Destination
        Given a bidirectional graph's edges and the time it takes to traverse each edge, i.e [u, v, time].
        Find the number of ways to reach the (n-1)th node from the 0th node in the shortest amount of time.

        We do a simple dijkstra but we also keep track of the number of ways to reach each node with minimum distance.
        The number of ways to reach the 0th node is 1 as its the starting node.
        Then if the distance to reach a node is less than the current distance,
            we update the distance and the number of ways to reach that node.
        If the distance to reach a node is equal to the current distance, we add the
            number of ways to reach that node to the current number of ways to reach that node.

        The answer is the number of ways to reach the (n-1)th node.

        Time complexity: O(ElogV), Space complexity: O(N)
            where   E is the number of edges,
                    V is the number of vertices,
                    N is the number of nodes (dist[n] + ways[n] + pq)
*/

constexpr int MOD = 1e9 + 7;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> graph(n);

        for ( auto& v : roads ) {
            graph[v[0]].push_back({ v[1], v[2] });
            graph[v[1]].push_back({ v[0], v[2] });
        }

        vector<long> dist(n, 1e12), ways(n, 0);
        priority_queue<pair<long, long>> pq;

        pq.push({ 0, 0 });
        dist[0] = 0;
        ways[0] = 1;

        while ( !pq.empty() ) {
            auto [d, q] = pq.top();
            pq.pop();
            d = -d;

            for ( auto& [nxt, time] : graph[q] ) {
                long k = 0L + d + time;
                if ( k < dist[nxt] ) {
                    dist[nxt] = k;
                    pq.push({ -dist[nxt], nxt });
                    ways[nxt] = ways[q];
                }
                else if ( k == dist[nxt] ) {
                    ways[nxt] = ( ways[nxt] + ways[q] ) % MOD;
                }
            }
        }
        return ways[n - 1] % MOD;
    }
};

int main() {
    Solution s;
    vector<vector<int>> roads = {
        {1,2,3},
        {1,3,3},
        {2,3,1},
        {1,4,2},
        {5,2,2},
        {3,5,1},
        {5,4,10}
    };
    cout << s.countPaths(5, roads) << '\n';
}
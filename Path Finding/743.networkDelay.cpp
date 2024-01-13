#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 743 - Network Delay Time
        There are n network nodes labeled from 1 to n. You are given times, a list of travel times as directed
            edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time
            it takes for a signal to travel from source to target.
        We will send a signal from a given node k. Return the time it takes for all the n nodes to receive the signal.
        If it is impossible for all the n nodes to receive the signal, return -1.

        We use a Dijkstra to find the time it takes for all the n nodes to receive the signal.
        We use a priority queue to store the current position and the time it takes for the signal to reach the current position.
        We use a visited array to keep track of the visited positions.
        We use a distance array to keep track of the time it takes for the signal to reach each position.
        Keep doing Dijkstra until we reach all the n nodes or the priority queue is empty.
        If we reach all the n nodes, return the maximum time it takes for the signal to reach a node.
        Else return -1.

        Time complexity: O(ElogV), Space complexity: O(n)
            where E is the number of edges.
*/

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<pair<int, int>>> graph;
        unordered_set<int> nodes;
        for ( auto& v : times ) {
            graph[v[0]].push_back({ v[1], v[2] });
            nodes.insert(v[0]);
            nodes.insert(v[1]);
        }

        if ( nodes.size() < n ) return -1;

        priority_queue<pair<int, int>> pq;
        unordered_map<int, bool> visited;
        unordered_map<int, int> dist;

        for ( auto& a : nodes ) dist[a] = 1e9, visited[a] = 0;

        pq.push({ 0, k });
        dist[k] = 0;

        while ( !pq.empty() ) {
            int cost = -pq.top().first;
            int node = pq.top().second;
            pq.pop();

            visited[node] = 1;

            for ( auto& [nxt, ncost] : graph[node] ) {
                if ( !visited[nxt] && cost + ncost < dist[nxt] ) {
                    dist[nxt] = cost + ncost;
                    pq.push({ -dist[nxt], nxt });
                }
            }
        }

        int mx = accumulate(dist.begin(), dist.end(), 0, [](int a, pair<int, int> b) {
            return max(a, b.second);
            });
        return mx == 1e9 ? -1 : mx;
    }
};

int main() {
    Solution s;
    vector<vector<int>> times = { {2,1,1},{2,3,1},{3,4,1} };
    cout << s.networkDelayTime(times, 4, 2) << '\n';
}
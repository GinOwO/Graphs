#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 787 - Cheapest Flights Within K Stops
        Given a list of edges connecting n cities and the cost of each edge, find the cheapest price from
            city src to city dst with at most k stops. If there is no such route, return -1.

        We use a BFS to find the cheapest price from city src to city dst with at most k stops.
        We use a queue to store the current position, the number of stops and the cost from src to the current position.
        We use a distance array to keep track of the cost from src to each city.
        Keep doing BFS until we the queue is empty.
        Only push the current position to the queue if the number of stops is less than or equal to k.

        If dist[dst] is not a sentinel value, return dist[dst].
        Else return -1.

        Time complexity: O(E), Space complexity: O(n)
            where E is the number of edges/flights.
*/

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);

        for ( auto& v : flights ) {
            graph[v[0]].push_back({ v[1], v[2] });
        }

        queue<pair<int, pair<int, int>>> q;
        vector<int> dist(n, 1e9);
        dist[src] = 0;

        q.push({ 0, {src, 0} });

        while ( !q.empty() ) {
            auto stops = q.front().first;
            auto [cur, d] = q.front().second;
            q.pop();

            if ( stops > k ) continue;
            for ( auto& [nxt, cost] : graph[cur] ) {
                if ( stops <= k && d + cost < dist[nxt] ) {
                    dist[nxt] = d + cost;
                    q.push({ stops + 1, {nxt, dist[nxt]} });
                }
            }
        }
        return dist[dst] == 1e9 ? -1 : dist[dst];
    }
};

int main() {
    Solution s;
    vector<vector<int>> flights = { {0,1,100},{1,2,100},{0,2,500} };
    cout << s.findCheapestPrice(3, flights, 0, 2, 1) << '\n';
}
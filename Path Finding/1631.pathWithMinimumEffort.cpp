#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 1631 - Path With Minimum Effort
        Given an m x n matrix of integers heights representing the height of each unit cell in a continent,
            return the minimum effort required to travel from the top-left cell to the bottom-right cell.
        Effort is defined as the maximum difference in heights between two adjacent cells in the path taken.

        We just do a Dijkstra from the starting point to the ending point. We use a priority queue to store the
            current position and the maximum difference in heights between two adjacent cells in the path taken.
        We store the maximum difference in the priority queue as a negative number so that the priority queue
            will be a min heap.
        We use a visited array to keep track of the visited positions and a distance array.
        The distance array is optional and the algorithm will still work without it, but albeit slower.
        Keep doing Dijkstra until we reach the ending point or the priority queue is empty.
        If we reach the ending point, return the maximum difference in heights between two adjacent cells in the path taken.
        Else return -1.
*/


constexpr int
rows[] = { -1, 0, 1, 0 },
cols[] = { 0, -1, 0, 1 };

class Solution {
public:
#define isValid(a,b,n,m) (a>=0 && a<n && b>=0 && b<m)
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, 0));
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        priority_queue<pair<int, pair<int, int>>> pq;

        pq.push({ 0, {0,0} });
        dist[0][0] = 1;

        while ( !pq.empty() ) {
            int d = -pq.top().first;
            auto [x, y] = pq.top().second;
            pq.pop();

            if ( x == n - 1 && y == m - 1 ) return d;

            visited[x][y] = 1;

            for ( int q = 0; q < 4; q++ ) {
                const int a = x + rows[q], b = y + cols[q];
                if ( isValid(a, b, n, m) && !visited[a][b] ) {
                    const int dd = max(d, abs(heights[x][y] - heights[a][b]));
                    if ( dist[a][b] > dd ) {
                        pq.push({ -dd, {a,b} });
                        dist[a][b] = dd;
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<vector<int>> heights = { {1,2,2},{3,8,2},{5,3,5} };
    cout << s.minimumEffortPath(heights);
}
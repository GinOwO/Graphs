#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 778 - Swim in Rising Water
        Given an n x m grid representing an elevation map. Find the minimum time required to swim from
            the top left corner of the grid to the bottom right corner. You can swim in any of the 4
            cardinal directions. But you can only move to a cell with height less than or equal to the height
            of the current cell. At a time t, the height of all cells is max(t, grid[i][j]). i.e height of lower
            cells increases with time.

        Same as 1631 but we use the condition max(d, grid[a][b]) instead of max(d, abs(heights[x][y] - heights[a][b])).
        And also set the priority queue to -grid[0][0] instead of 0.
*/

#define isValid(a,b,n,m) (a>=0 && a<n && b>=0 && b<m)

constexpr int
rows[] = { -1, 0, 1, 0 },
cols[] = { 0, -1, 0, 1 };

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, 0));
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        priority_queue<pair<int, pair<int, int>>> pq;

        pq.push({ -grid[0][0], {0,0} });

        while ( !pq.empty() ) {
            int d = -pq.top().first;
            auto [x, y] = pq.top().second;
            pq.pop();

            if ( x == n - 1 && y == m - 1 ) return d;

            visited[x][y] = 1;

            for ( int q = 0; q < 4; q++ ) {
                const int a = x + rows[q], b = y + cols[q];
                if ( isValid(a, b, n, m) && !visited[a][b] ) {
                    const int dd = max(d, grid[a][b]);
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
    vector<vector<int>> grid = { {0,0,0},{1,1,0},{1,1,0} };
    cout << s.swimInWater(grid);
}
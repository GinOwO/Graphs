#include <bits/stdc++.h>

using namespace std;

/*
    LeetCode 2812 - Find the Safest Path in a Grid
        Given a grid of size n x n, each cell of the grid is either 0(empty) or a 1(thief).
        The safeness of a level is defined as the Manhattan distance between the cell and the nearest cell with a thief.
        You need to move from (0, 0) to (n-1, n-1). Find the maximum safeness factor of a path from (0, 0) to (n-1, n-1).

        First use BFS to calculate the safeness of all the cells:
            We first add all the cells with a thief to a queue and set their safeness to 0.
            Then we do a BFS from the cells with a thief and update the safeness of all the cells.
            Keep track of the largest value of safeness in mx.
        Then do a binary search from 0 -> mx, for each value check if there is a valid path from (0, 0) to (n-1, n-1) which has minimum safeness of mid.
        If there is a valid path, set l = mid + 1.
        Else set r = mid - 1.

        The answer is r.

        Note: An edge case is if all the cells are thieves, then r will be the sentinel value INT_MIN, so we return 0 instead.

        Time complexity: O(n^2 * log(n)), Space complexity: O(n^2)
*/

#define isValid(a,b,n) (a>=0 && a<n && b>=0 && b<n)

constexpr int dirs[] = { 0, 1, 0, -1, 0 };

class Solution {
    bool hasValidPath(const vector<vector<int>>& distToThief, int safeness) {
        if ( distToThief[0][0] < safeness ) return false;

        const int n = distToThief.size();
        queue<pair<int, int>> q { {{0, 0}} };
        vector<vector<bool>> seen(n, vector<bool>(n));
        seen[0][0] = true;

        while ( !q.empty() ) {
            auto [i, j] = q.front();
            q.pop();
            if ( distToThief[i][j] < safeness ) continue;
            if ( i == n - 1 && j == n - 1 ) return true;
            for ( int x = 0; x < 4; x++ ) {
                const int a = i + dirs[x], b = j + dirs[x + 1];
                if ( isValid(a, b, n) && !seen[a][b] ) {
                    q.emplace(a, b);
                    seen[a][b] = true;
                }
            }
        }
        return false;
    }

public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size(), mx = INT_MIN;

        vector<vector<bool>> visited(n, vector<bool>(n, false));
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        queue<pair<int, int>> q;

        for ( int i = 0; i < n; i++ ) {
            for ( int j = 0; j < n; j++ ) {
                if ( grid[i][j] ) {
                    q.push({ i, j });
                    visited[i][j] = 1;
                    dist[i][j] = 0;
                }
            }
        }

        while ( !q.empty() ) {
            auto [x, y] = q.front();
            q.pop();

            visited[x][y] = 1;

            for ( int i = 0; i < 4; i++ ) {
                const int a = x + dirs[i], b = y + dirs[i + 1];
                if ( isValid(a, b, n) && !visited[a][b] && !grid[a][b] && dist[a][b] > dist[x][y] + 1 ) {
                    q.push({ a, b });
                    dist[a][b] = dist[x][y] + 1;
                    mx = max(dist[a][b], mx);
                }
            }
        }

        int l = 0, r = mx, mid;
        while ( l <= r ) {
            mid = l + ( r - l ) / 2;
            if ( hasValidPath(dist, mid) ) l = mid + 1;
            else r = mid - 1;
        }
        return r == INT_MIN ? 0 : r;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = { {1,0,0},{0,0,0},{0,0,1} };
    cout << s.maximumSafenessFactor(grid) << '\n';
    return 0;
}
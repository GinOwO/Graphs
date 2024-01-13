#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 310 - Shortest Path in Binary Matrix
        Given an n x n binary matrix grid, return the length of the shortest path from (0, 0) to (n - 1, n - 1).
        You can only move to a cell with value 0. You can move in any of the 8 directions.
        If no such path exists, return -1.

        We use a BFS to find the shortest path from (0, 0) to (n - 1, n - 1).
        We use a queue to store the current position and the distance from (0, 0) to the current position.
        We use a visited array to keep track of the visited positions.
        Keep doing BFS until we reach (n - 1, n - 1) or the queue is empty.
        If we reach (n - 1, n - 1), return the distance from (0, 0) to (n - 1, n - 1).
        Else return -1.

        Time complexity: O(n^2), Space complexity: O(n^2)
*/

class Solution {
public:
#define isValid(a,b,n) (a>=0 && a<n && b>=0 && b<n)
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if ( grid[0][0] || grid[n - 1][n - 1] ) return -1;

        vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, 0));
        queue<pair<int, pair<int, int>>> q;

        q.push({ 1, {0,0} });
        visited[0][0] = 1;

        while ( !q.empty() ) {
            int d = q.front().first;
            auto [x, y] = q.front().second;
            q.pop();

            for ( int i = -1; i < 2; i++ ) {
                for ( int j = -1; j < 2; j++ ) {
                    const int a = x + i, b = y + j;
                    if ( isValid(a, b, n) && !visited[a][b] && !grid[a][b] ) {
                        if ( a == n - 1 && b == n - 1 ) return d + 1;
                        q.push({ d + 1,{a, b} });
                        visited[a][b] = 1;
                    }
                }
            }
        }
        return n == 1 ? !grid[0][0] : -1;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = { {0,0,0},{1,1,0},{1,1,0} };
    cout << s.shortestPathBinaryMatrix(grid);
}
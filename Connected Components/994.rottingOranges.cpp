#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 994 - Rotting Oranges
        Given a grid of oranges, find the minimum time it takes for all the oranges to rot.
        An orange rots if it is adjacent to a rotten orange. An orange is adjacent to another
        orange if it is above, below, left, or right of it.

        Example:
            [[2,1,1],
             [1,1,0],
             [0,1,1]]
            ans = 4

        We do a BFS with (x,y,time). Add all initial rotten oranges to the queue.
        Then perform BFS with queue. If in any of the cardinal directions, there is an orange which is not rotten,
        then add it to the queue and mark it as rotten. Also, mark it as visited so that we don't add it to the queue again.
        We increment the time by 1. Once the queue is empty, we check if there are any oranges left. If there are, then return -1.
        Else, return the max time.

        Time: O(n*m), Space: O(n*m)

*/

#define isValid(i,j,m,n) (i>=0 && i<m && j>=0 && j<n)

typedef struct Cell {
    int x, y, t;
    Cell(int a, int b, int c) {
        x = a; y = b; t = c;
    }
} Cell;

constexpr int
rows[] = { -1, 0, 1, 0 },
cols[] = { 0, -1, 0, 1 };

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), ans = 0, a, b, t, cnt = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, 0));
        queue<Cell> que;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    que.push({ i, j, 0 });
                    visited[i][j] = 1;
                }
                else if (grid[i][j]) cnt++;
            }
        }

        while (!que.empty()) {
            a = que.front().x;
            b = que.front().y;
            t = que.front().t;
            ans = max(ans, t);
            que.pop();
            for (int k = 0; k < 4; k++) {
                int i = a + rows[k], j = b + cols[k];
                if (isValid(i, j, m, n) && grid[i][j] && !visited[i][j]) {
                    que.push({ i, j, t + 1 });
                    visited[i][j] = 1;
                    cnt--;
                }
            }
        }

        return cnt ? -1 : ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = { {2,1,1},{1,1,0},{0,1,1} };
    cout << s.orangesRotting(grid) << endl;
    return 0;
}
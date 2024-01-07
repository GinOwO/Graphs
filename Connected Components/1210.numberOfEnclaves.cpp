#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 1210 - Number of Enclaves
        Given a grid of 0s and 1s, find the number of 1s that are not connected to the boundary.
        A 1 is connected to the boundary if it is on the boundary or if it is connected to a 1 that is on the boundary.

        Example:
            [[0,0,0,0],
             [1,0,1,0],
             [0,1,1,0],
             [0,0,0,0]]
            ans = 1

        We do a DFS/BFS from all the boundary 1s. If we encounter a 1, then we mark it in the visited matrix.

        Finally, we count all the 1s that are not visited.

        Time: O(n*m), Space: O(n*m)
*/

#define isValid(i,j,m,n) (i>=0 && i<m && j>=0 && j<n)

typedef struct Cell {
    int x, y;
    Cell(int a, int b) {
        x = a; y = b;
    }
} Cell;

constexpr int
rows[] = { -1, 0, 1, 0 },
cols[] = { 0, -1, 0, 1 };

class Solution {
public:
    void boundaryDFS(int a, int b, int m, int n, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        visited[a][b] = 1;

        for (int i = 0; i < 4; i++) {
            int x = a + rows[i], y = b + cols[i];
            if (isValid(x, y, m, n) && !visited[x][y] && grid[x][y] == 1)
                boundaryDFS(x, y, m, n, grid, visited);
        }
    }

    int numEnclavesDFS(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, 0));

        for (int i = 0; i < m; i++) {
            if (!visited[i][0] && grid[i][0] == 1)
                boundaryDFS(i, 0, m, n, grid, visited);

            if (!visited[i][n - 1] && grid[i][n - 1] == 1)
                boundaryDFS(i, n - 1, m, n, grid, visited);
        }

        for (int i = 0; i < n; i++) {
            if (!visited[0][i] && grid[0][i] == 1)
                boundaryDFS(0, i, m, n, grid, visited);

            if (!visited[m - 1][i] && grid[m - 1][i] == 1)
                boundaryDFS(m - 1, i, m, n, grid, visited);
        }

        int ans = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] && !visited[i][j]) ans++;

        return ans;
    }

    int numEnclavesBFS(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), a, b;
        vector<vector<bool>> visited(m, vector<bool>(n, 0));
        queue<Cell> que;

        for (int i = 0; i < m; i++) {
            if (!visited[i][0] && grid[i][0] == 1) {
                que.push({ i,0 });
                visited[i][0] = 1;
            }

            if (!visited[i][n - 1] && grid[i][n - 1] == 1) {
                que.push({ i,n - 1 });
                visited[i][n - 1] = 1;
            }
        }

        for (int i = 0; i < n; i++) {
            if (!visited[0][i] && grid[0][i] == 1) {
                que.push({ 0,i });
                visited[0][i] = 1;
            }

            if (!visited[m - 1][i] && grid[m - 1][i] == 1) {
                que.push({ m - 1,i });
                visited[m - 1][i] = 1;
            }
        }

        while (!que.empty()) {
            a = que.front().x;
            b = que.front().y;
            que.pop();

            for (int k = 0; k < 4; k++) {
                int i = a + rows[k], j = b + cols[k];
                if (isValid(i, j, m, n) && grid[i][j] && !visited[i][j]) {
                    que.push({ i, j });
                    visited[i][j] = 1;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] && !visited[i][j]) ans++;
        return ans;
    }

    int numEnclaves(vector<vector<int>>& grid) {
        return numEnclavesBFS(grid);
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = { {0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0} };
    cout << s.numEnclaves(grid) << endl;
    return 0;
}
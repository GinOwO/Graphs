#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 542 - 01 Matrix
        Given a matrix of 0s and 1s, find the distance of each cell from the nearest 0.
        The distance between two adjacent cells is 1.

        Example:
            [[0,0,0],
             [0,1,0],
             [1,1,1]]
            ans = [[0,0,0],
                   [0,1,0],
                   [1,2,1]]

        We do a BFS with (x,y,d). Add all initial 0s to the queue.
        Then perform BFS with queue. Store the distance in a distance matrix.
        If in any of the cardinal directions, there is a 1 which is not visited,
            then add it to the queue and mark it as visited.
        Once the queue is empty, return the distance matrix.

        Time: O(n*m), Space: O(n*m)


*/

#define isValid(i,j,m,n) (i>=0 && i<m && j>=0 && j<n)

typedef struct Cell {
    int x, y, d;
    Cell(int a, int b, int c) {
        x = a; y = b; d = c;
    }
} Cell;

constexpr int
rows[] = { -1, 0, 1, 0 },
cols[] = { 0, -1, 0, 1 };

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int a, b, d;
        const int m = mat.size(), n = mat[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, 0));
        vector<vector<int>> dist(m, vector<int>(n, 0));
        queue<Cell> que;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    que.push({ i,j,0 });
                    visited[i][j] = 1;
                }
            }
        }

        while (!que.empty()) {
            a = que.front().x;
            b = que.front().y;
            d = que.front().d;
            que.pop();
            dist[a][b] = d;

            for (int k = 0; k < 4; k++) {
                int i = a + rows[k], j = b + cols[k];
                if (isValid(i, j, m, n) && mat[i][j] && !visited[i][j]) {
                    visited[i][j] = 1;
                    que.push({ i,j,d + 1 });
                }
            }
        }

        return dist;
    }
};

int main() {
    Solution s;
    vector<vector<int>> mat = { {0,0,0},{0,1,0},{1,1,1} };
    vector<vector<int>> ans = s.updateMatrix(mat);

    for (auto& a : ans) {
        for (auto& b : a) cout << b << " ";
        cout << endl;
    }
    return 0;
}
#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 130 - Surrounded Regions
        Given a grid of 'X's and 'O's, flip all the 'O's that are surrounded by 'X's to 'X'.
        A 'O' is surrounded by 'X' if it is not on the boundary and all the adjacent cells are 'X'.

        Example:
            [['X','X','X','X'],
             ['X','O','O','X'],
             ['X','X','O','X'],
             ['X','O','X','X']]
            ans = [['X','X','X','X'],
                   ['X','X','X','X'],
                   ['X','X','X','X'],
                   ['X','O','X','X']]

        We do a DFS from all the boundary 'O's. If we encounter a 'O', then we mark it in the visited matrix.

        Finally, we change all the 'O's that are not visited to 'X'.

        Time: O(n*m), Space: O(n*m)
*/

#define isValid(i,j,m,n) (i>=0 && i<m && j>=0 && j<n)

constexpr int
rows[] = { -1, 0, 1, 0 },
cols[] = { 0, -1, 0, 1 };

class Solution {
public:
    void boundaryDFS(int a, int b, int m, int n, vector<vector<char>>& board, vector<vector<bool>>& visited) {
        visited[a][b] = 1;

        for (int i = 0; i < 4; i++) {
            int x = a + rows[i], y = b + cols[i];
            if (isValid(x, y, m, n) && !visited[x][y] && board[x][y] == 'O')
                boundaryDFS(x, y, m, n, board, visited);
        }
    }

    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, 0));

        for (int i = 0; i < m; i++) {
            if (!visited[i][0] && board[i][0] == 'O')
                boundaryDFS(i, 0, m, n, board, visited);

            if (!visited[i][n - 1] && board[i][n - 1] == 'O')
                boundaryDFS(i, n - 1, m, n, board, visited);
        }

        for (int i = 0; i < n; i++) {
            if (!visited[0][i] && board[0][i] == 'O')
                boundaryDFS(0, i, m, n, board, visited);

            if (!visited[m - 1][i] && board[m - 1][i] == 'O')
                boundaryDFS(m - 1, i, m, n, board, visited);
        }

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (!visited[i][j] && board[i][j] == 'O') board[i][j] = 'X';
    }
};

int main() {
    Solution s;
    vector<vector<char>> board = { {'O','X','X','O','X'},{'X','O','O','X','O'},{'X','O','X','O','X'},{'O','X','O','O','O'},{'X','X','O','X','O'} };
    s.solve(board);

    for (auto& a : board) {
        for (auto& b : a) cout << b << " ";
        cout << endl;
    }
    return 0;
}
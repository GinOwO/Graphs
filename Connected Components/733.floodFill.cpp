#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 733 - Flood Fill
        Given an m x n array, color all the points with c if they are
        connected to the starting point and has the same color as starting point.

        Example:
            [[1,1,1],
             [1,1,0],
             [1,0,1]]
            sr = 1, sc = 1, c = 2

            [[2,2,2],
             [2,2,0],
             [2,0,1]]

        Just DFS from the starting point and change the color of all the points.
        Only color the points that has the same color as the starting point.

        An exception is if the starting point has the same color as the new color,
        then we don't need to do anything.

        Time: O(n*m), Space: O(n*m)
*/

#define isValid() (i+a>=0 && i+a<image.size() && j+b>=0 && j+b<image[0].size() && image[i+a][j+b]==ini)

constexpr int
rows[] = { -1, 0, 1, 0 },
cols[] = { 0, -1, 0, 1 };

class Solution {
public:
    void DFS(vector<vector<int>>& image, int i, int j, int c, int ini) {
        image[i][j] = c;
        for (int x = 0; x < 4; x++) {
            int a = rows[x], b = cols[x];
            if (isValid()) DFS(image, i + a, b + j, c, ini);
        }
    }

    vector<vector<int>>& floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        if (image[sr][sc] == color) return image;
        DFS(image, sr, sc, color, image[sr][sc]);
        return image;
    }
};

int main() {
    Solution s;
    vector<vector<int>> image = { {0,0,0}, {0,0,0} };
    s.floodFill(image, 0, 0, 0);

    for (auto& a : image) {
        for (auto& b : a) cout << b << " ";
        cout << endl;
    }
    return 0;
}
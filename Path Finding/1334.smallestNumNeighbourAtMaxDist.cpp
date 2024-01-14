#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 1334 - Find the City With the Smallest Number of Neighbors at a Threshold Distance
        Given a bidirectional graph's edges and the distance it takes to traverse each edge, i.e [u, v, dist].
        Find the city with the smallest number of neighbors at a threshold distance from it.

        We make an adjaceny matrix and do a simple Floyd Warshall to find the shortest distance between each pair of nodes.
        Then we iterate through each node and count the number of nodes that are at most the threshold distance away from it.
        If the number of nodes is less than or equal to the current minimum, we update the minimum and the answer.

        Time complexity: O(V^3), Space complexity: O(V^2)
            where   V is the number of vertices
*/

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> adjMatrix(n, vector<int>(n, 1e9));

        for ( int i = 0; i < n; i++ ) adjMatrix[i][i] = 0;
        for ( auto& edge : edges ) {
            adjMatrix[edge[0]][edge[1]] = edge[2];
            adjMatrix[edge[1]][edge[0]] = edge[2];
        }

        for ( int k = 0; k < n; k++ ) {
            for ( int i = 0; i < n; i++ ) {
                for ( int j = 0; j < n; j++ ) {
                    adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
                }
            }
        }

        int cnt = 1e9, mx = -1, cur;
        for ( int i = 0; i < n; i++ ) {
            cur = 0;
            for ( int j = 0; j < n; j++ ) {
                if ( adjMatrix[i][j] <= distanceThreshold )cur++;
            }
            if ( cur <= cnt ) mx = i, cnt = cur;
        }

        return mx;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> edges = { {0,1,3},{1,2,1},{1,3,4},{2,3,1} };
    cout << sol.findTheCity(4, edges, 4) << endl;

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 947 - Most Stones Removed with Same Row or Column
        Given a list of stones' positions (x, y), remove the stones that share the same row or column with other stones.
        What is the maximum number of moves we can make?

        We can use a DSU to find the number of connected components.
        The idea here is to make the row number as the parent node. Since the remaining stones at the end will be equal
            to the number of connected components. We just need to find the number of unique parents in the DSU.
            We will use the row number as the parent node. So initially there will be maxRow possible parents.
            For each stone we will represent it as maxRow+col+1. This is because we need to differentiate between the row and column.
            Then we will make a connection between (row, maxRow+col+1) in the DSU. This will make the row as the parent node.
            Now for all other nodes in the same row or column, when added to the DSU will take this as the parent. Hence connecting them.
            Finally we will count the number of unique parents in the DSU.

        The answer is the number of stones - the number of connected components.

        Time Complexity: O(n), Space Complexity: O(n)
            where   n is the number of stones. This is just for iterating through the stones once.
            For the DSU operations alone it is O(4*α(n)) ≈ O(4) ≈ O(1) where α is the inverse Ackermann function.
*/

class DisjointSetRank {
    vector<int> parent, rank;
public:
    DisjointSetRank(int n) : parent(n + 1), rank(n + 1, 0) {
        for ( int i = 0; i <= n; i++ ) {
            parent[i] = i;
        }
    }

    void insertEdge(int u, int v) {
        int parentU = findParent(u);
        int parentV = findParent(v);

        if ( parentU == parentV ) return;

        if ( rank[parentU] < rank[parentV] ) {
            parent[parentU] = parentV;
        }
        else if ( rank[parentU] < rank[parentV] ) {
            parent[parentV] = parentU;
        }
        else {
            parent[parentV] = parentU;
            rank[parentU]++;
        }
    }

    bool isConnected(int u, int v) {
        return findParent(u) == findParent(v);
    }

    int findParent(int node) {
        if ( parent[node] == node ) return node;
        return parent[node] = findParent(parent[node]);
    }
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int maxRow = 0, maxCol = 0, n = stones.size();
        for ( auto& v : stones ) {
            maxRow = max(v[0], maxRow);
            maxCol = max(v[1], maxCol);
        }

        DisjointSetRank dsu(maxRow + maxCol + 1);
        unordered_set<int> seen;

        for ( auto& v : stones ) {
            int a = v[0], b = maxRow + v[1] + 1;
            seen.insert(a); seen.insert(b);
            dsu.insertEdge(a, b);
        }

        int cnt = 0;
        for ( auto& c : seen ) {
            if ( dsu.findParent(c) == c ) {
                cnt++;
            }
        }

        return n - cnt;
    }
};

int main() {
    Solution s;
    vector<vector<int>> stones = { {0,0},{0,1},{1,0},{1,2},{2,1},{2,2} };
    cout << s.removeStones(stones) << endl;
    return 0;
}
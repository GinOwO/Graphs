#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 547 - Number of Provinces
        This is an alternative solution to the Leetcode 547 - Number of Provinces problem.
        Instead of using DFS, we use a DSU to find the number of connected components.
        We create a DSU and add all the edges to it.
        Then we just count the number of unique parents in the DSU, which can be done in two ways:
            1. We can use a set to store the parents and then return the size of the set.
            2. We can just count only those nodes whose parent is itself.

        Time Complexity: O(n^2), Space Complexity: O(n)
            The time complexity is O(n^2) because we have to iterate through the entire matrix.
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

    int findParent(int node) {
        if ( parent[node] == node ) return node;
        return parent[node] = findParent(parent[node]);
    }

    bool isConnected(int u, int v) {
        return findParent(u) == findParent(v);
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        const int n = isConnected.size();
        DisjointSetRank dsu(n);
        for ( int i = 0; i < n; i++ ) {
            for ( int j = 0; j < n; j++ ) {
                if ( isConnected[i][j] ) {
                    dsu.insertEdge(i, j);
                }
            }
        }

        unordered_set<int> st;
        for ( int i = 0; i < n; i++ ) {
            st.insert(dsu.findParent(i));
        }

        return st.size();
    }
};
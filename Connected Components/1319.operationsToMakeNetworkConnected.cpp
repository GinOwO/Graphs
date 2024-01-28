#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 1319 - Number of Operations to Make Network Connected
        Given a bidirectional graph's edges, find the minimum number of edges to add to make the graph connected.
        You cannot increase the total number of edges in the graph, i.e you must remove an edge before adding a new one.

        We will use a DSU to solve this. We know that the answer to connect n unconnected groups is (n-1).
        So the answer is the number of unconnected groups - 1. But we also have to check if there are enough edges to
            connect all the groups. If there are not enough edges, we return -1.
        So we will simply count the number of extra edges. An extra edge is an edge that connects two nodes that are already connected.
        So if we use isConnected(u, v) to check if u and v are connected, we increment extra.
        Else we insert the edge using insertEdge(u, v).

        Finally if extra >= notConnected - 1, we return notConnected - 1.
        Else we return -1.

        Time Complexity: O(n), Space Complexity: O(n)
            where   n is the number of nodes. This is just for iterating through the vertices once.
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
        else if ( rank[parentV] < rank[parentU] ) {
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
    int makeConnected(int n, vector<vector<int>>& connections) {
        DisjointSetRank dsu(n);

        int extra = 0, notConnected = 0;
        for ( auto& v : connections ) {
            if ( dsu.isConnected(v[0], v[1]) ) extra++;
            else dsu.insertEdge(v[0], v[1]);
        }

        for ( int i = 0; i < n; i++ ) {
            if ( dsu.findParent(i) == i ) notConnected++;
        }

        if ( extra >= notConnected - 1 ) return notConnected - 1;
        return -1;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> connections = { {0,1},{0,2},{0,3},{1,2},{1,3} };
    cout << sol.makeConnected(6, connections) << endl;
    return 0;
}
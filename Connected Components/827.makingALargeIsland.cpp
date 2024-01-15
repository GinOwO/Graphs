#include <bits/stdc++.h>

using namespace std;

class DisjointSetSize {
    vector<int> parent, size;
public:
    DisjointSetSize(int n) : parent(n + 1), size(n + 1, 1) {
        for ( int i = 0; i <= n; i++ ) {
            parent[i] = i;
        }
    }

    void insertEdge(int u, int v) {
        int parentU = findParent(u);
        int parentV = findParent(v);

        if ( parentU == parentV ) return;

        if ( size[parentU] < size[parentV] ) {
            parent[parentU] = parentV;
            size[parentV] += size[parentU];
        }
        else {
            parent[parentV] = parentU;
            size[parentU] += size[parentV];
        }
    }

    bool isConnected(int u, int v) {
        return findParent(u) == findParent(v);
    }

    int findParent(int node) {
        if ( parent[node] == node ) return node;
        return parent[node] = findParent(parent[node]);
    }

    int findSize(int node) {
        return size[findParent(node)];
    }
};

constexpr int dirs[] = { 0, -1, 0, 1, 0 };

class Solution {
public:
#define isValid(i,j,n) (i>=0 && i<n && j>=0 && j<n)
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        DisjointSetSize ds(n * n);

        for ( int row = 0; row < n; row++ ) {
            for ( int col = 0; col < n; col++ ) {
                if ( grid[row][col] == 0 ) continue;
                for ( int i = 0; i < 4; i++ ) {
                    int a = row + dirs[i];
                    int b = col + dirs[i + 1];
                    if ( isValid(a, b, n) && grid[a][b] == 1 ) {
                        int node = row * n + col;
                        int adjNode = a * n + b;
                        ds.insertEdge(node, adjNode);
                    }
                }
            }
        }

        int mx = 0;
        for ( int row = 0; row < n; row++ ) {
            for ( int col = 0; col < n; col++ ) {
                if ( grid[row][col] == 1 ) continue;
                set<int> st;
                for ( int i = 0; i < 4; i++ ) {
                    int a = row + dirs[i];
                    int b = col + dirs[i + 1];
                    if ( isValid(a, b, n) ) {
                        if ( grid[a][b] == 1 ) {
                            st.insert(ds.findParent(a * n + b));
                        }
                    }
                }
                int size = 0;
                for ( auto it : st ) {
                    size += ds.findSize(it);
                }
                mx = max(mx, size + 1);
            }
        }
        for ( int i = 0; i < n * n; i++ ) {
            mx = max(mx, ds.findSize(ds.findParent(i)));
        }
        return mx;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = { {1,0},{0,1} };
    cout << s.largestIsland(grid) << endl;
    return 0;
}
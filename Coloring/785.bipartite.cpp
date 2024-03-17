#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 785 - Is Graph Bipartite?
        Given an undirected graph, return true if it is bipartite, false otherwise.
        A graph is bipartite if we can divide the vertices into two disjoint sets such that all edges are between the two sets.

        Example:
            [[1,3],
             [0,2],
             [1,3],
             [0,2]]
            ans = true

        We do a BFS/DFS from all the unvisited vertices. If we encounter a vertex that is already visited, then we check if it is of the same color as the current vertex.
        If it is, then the graph is not bipartite. Else, we continue.
        If we encounter a vertex that is not visited, then we mark it with the opposite color of the current vertex and continue.

        Time: O(n+m), Space: O(n)
*/

static int color [ 101 ];
class Solution {
public:
    bool dfs( const vector<vector<int>>& graph, int i, int prev, int color[] ) {
        color [ i ] = prev;

        for ( auto& v : graph [ i ] ) {
            if ( color [ v ] == -1 ) {
                if ( !dfs( graph, v, !prev, color ) ) return false;
            }
            else if ( color [ v ] == color [ i ] ) {
                return false;
            }
        }
        return true;
    }

    bool bfs( const vector<vector<int>>& graph, int start, int color[] ) {
        queue<int> que;
        que.push( start );
        color [ start ] = 0;

        while ( !que.empty( ) ) {
            int i = que.front( );
            que.pop( );

            for ( auto& v : graph [ i ] ) {
                if ( color [ v ] == -1 ) {
                    color [ v ] = !color [ i ];
                    que.push( v );
                }
                else if ( color [ v ] == color [ i ] ) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite( vector<vector<int>>& graph ) {
        memset( color, -1, sizeof( int ) * 101 );

        for ( int i = 0; i < graph.size( ); i++ ) {
            if ( color [ i ] == -1 ) {
                if ( !bfs( graph, i, color ) ) return false;
                // if(!dfs(graph, i, 0, color)) return false;
            }
        }
        return true;
    }
};

int main( ) {
    Solution s;
    vector<vector<int>> adjList = {
        { 1, 3 },
        { 0, 2 },
        { 1, 3 },
        { 0, 2 }
    };

    cout << s.isBipartite( adjList ) << endl;
    return 0;
}
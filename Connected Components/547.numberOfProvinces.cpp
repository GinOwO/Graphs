#include<bits/stdc++.h>

using namespace std;

/*
    Leetcode 547 - Number of Provinces
        Normal DFS. Set Visited array to true when visiting a node.
        Then DFS all the nodes connected to it that are not visited yet.
        Once its done, find the next index of visited that is false and repeat.
        The number of times you need to find the next index of visited that is false is the answer.

        Time Complexity: O(n^2), Space Complexity: O(n)
*/

class Solution {
public:
    void DFS(int k, const vector<vector<int>>& graph, vector<bool>& visited) {
        visited[k] = 1;
        for (int i = 0; i < graph[k].size(); i++)
            if (graph[k][i] && !visited[i]) DFS(i, graph, visited);
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        const int n = isConnected.size();
        vector<bool> visited(n, 0); int cnt = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                DFS(i, isConnected, visited);
                cnt++;
            }
        }
        return cnt;
    }
};

int main() {
    Solution s;
    vector<vector<int>> isConnected = { {1,0,0},{0,1,0},{0,0,1} };
    cout << s.findCircleNum(isConnected) << endl;
    return 0;
}
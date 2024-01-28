#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 721 - Accounts Merge
        Given a list of accounts where each account is represented as a list of strings, i.e [name, mail1, mail2, ...].
        Merge all the accounts that have the same email address.
        The output should be a list of accounts where each account is represented as a list of strings, i.e [name, mail1, mail2, ...].

        We use a DSU to merge all the accounts that have the same email address.
        We use the index of the account as the parent node.
        Then we iterate through all the accounts and for each account we iterate through all the emails.
        We add each email to a map that maps the email to the index of the account.
        If an email is already in the map, we merge the two accounts using the DSU.
        Finally we iterate through all the accounts and add all the emails to a vector.
        Then we sort the vector and add the name of the account to the front of the vector.
        Then we add this vector to the answer.

        Time Complexity: O(n*mlogm), Space Complexity: O(M)
            where   n is the number of accounts
                    m is the maximum number of emails in an account
                    M is the total number of emails in all the accounts
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
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DisjointSetRank dsu(n);
        unordered_map<string, int> mails;
        vector<vector<string>> merged(n);
        vector<vector<string>> ans;

        for ( int i = 0; i < n; i++ ) {
            for ( int j = 1; j < accounts[i].size(); j++ ) {
                auto& mail = accounts[i][j];
                if ( !mails.count(mail) ) {
                    mails[mail] = i;
                }
                else {
                    dsu.insertEdge(i, mails[mail]);
                }
            }
        }

        for ( auto& [mail, val] : mails ) {
            merged[dsu.findParent(val)].push_back(mail);
        }

        for ( int i = 0; i < n; i++ ) {
            auto& v = merged[i];
            if ( !v.size() ) continue;
            sort(v.begin(), v.end());
            ans.push_back({ accounts[i][0] });
            for ( auto& s : v ) ans.back().push_back(s);
        }

        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<string>> accounts = { {"John","johnsmith@mail.com","john_newyork@mail.com"},
    {"John","johnsmith@mail.com","john00@mail.com"},{"Mary","mary@mail.com"},{"John","johnnybravo@mail.com"} };

    auto ans = s.accountsMerge(accounts);
    for ( auto& v : ans ) {
        for ( auto& s : v ) cout << s << " ";
        cout << endl;
    }

    return 0;


}
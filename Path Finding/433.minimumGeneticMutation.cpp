#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 433 - Minimum Genetic Mutation
        Starting gene, target/ending gene, list of possible intermediate genes (excl startingGene).
        In one operation, change one character of the gene to any other character such that
            the new gene is in the list of possible intermediate genes.
        Return the minimum number of operations required to change the starting gene to the ending gene.
        If it is not possible, return -1.

        Same as 127.wordLadder.cpp, except that we have a charater set of 4 instead of 26.

        Time: O(n*m*4), Space: O(n)
            Where n = number of genes in bank, m = length of gene
*/

class Solution {
public:
    int minMutation(const string& startGene, const string& endGene, const vector<string>& bank) {
        const int n = startGene.size();
        unordered_set<string> st(bank.begin(), bank.end());
        queue<pair<string, int>> q;

        q.push({ startGene, 0 });

        while ( !q.empty() ) {
            auto [s, d] = q.front();
            q.pop();
            if ( s == endGene ) return d;

            for ( int i = 0; i < n; i++ ) {
                char x = s[i];
                for ( auto& j : "ACGT" ) {
                    s[i] = j;
                    if ( st.count(s) ) {
                        st.erase(s);
                        q.push({ s, d + 1 });
                    }
                }
                s[i] = x;
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    string startGene = "AACCGGTT";
    string endGene = "AAACGGTA";
    vector<string> bank = { "AACCGGTA", "AACCGCTA", "AAACGGTA" };
    cout << sol.minMutation(startGene, endGene, bank) << endl;

    return 0;
}
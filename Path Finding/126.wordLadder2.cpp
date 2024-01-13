#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 126 - Word Ladder II
        Starting word, target/ending word, list of possible intermediate words (incl start and ending words).
        In one operation, change one character of the word to any other character such that
            the new word is in the list of possible intermediate words.
        Return all the shortest transformation sequences from start to end, or an empty list if no such sequence exists.
        Each sequence should be returned as a list of the words.
        Note that the words in the sequence should be ordered lexicographically.

        First we find the length of the shortest transformation sequence from start to end.
        Then we backtrack from the end word to the start word to find all the sequences of the shortest length using a DFS.
*/

class Solution {
    unordered_map<string, int> mp;
    vector<vector<string>> ans;
    string b;
private:
    void dfs(string s, vector<string>& seq) {
        if ( s == b ) {
            reverse(seq.begin(), seq.end());
            ans.push_back(seq);
            reverse(seq.begin(), seq.end());
            return;
        }

        int n = s.size();
        int d = mp[s];

        for ( int i = 0; i < n; i++ ) {
            char w = s[i];
            for ( char c = 'a'; c <= 'z'; c++ ) {
                s[i] = c;
                if ( mp.count(s) && mp[s] + 1 == d ) {
                    seq.push_back(s);
                    dfs(s, seq);
                    seq.pop_back();
                }
            }
            s[i] = w;
        }
    }

public:
    vector<vector<string>> findLadders(string start, string end, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<string> q;
        b = start;
        q.push({ start });

        mp[start] = 1;
        int n = start.size();
        st.erase(start);

        while ( !q.empty() ) {
            auto s = q.front();
            int d = mp[s];
            q.pop();

            if ( s == end ) break;
            for ( int i = 0; i < n; i++ ) {
                char w = s[i];
                for ( char c = 'a'; c <= 'z'; c++ ) {
                    s[i] = c;
                    if ( st.count(s) ) {
                        q.push(s);
                        st.erase(s);
                        mp[s] = d + 1;
                    }
                }
                s[i] = w;
            }
        }

        if ( mp.count(end) ) {
            vector<string> seq;
            seq.push_back(end);
            dfs(end, seq);
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<string> wordList = { "hot", "dot", "dog", "lot", "log", "cog" };
    vector<vector<string>> ans = s.findLadders("hit", "cog", wordList);
    for ( auto& x : ans ) {
        for ( auto& y : x ) cout << y << " ";
        cout << endl;
    }
    return 0;
}
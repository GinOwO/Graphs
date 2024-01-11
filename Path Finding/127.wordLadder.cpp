#include <bits/stdc++.h>

using namespace std;

/*
    Leetcode 127 - Word Ladder
        Starting word, target/ending word, list of possible intermediate words (incl start and ending words).
        In one operation, change one character of the word to any other character such that
            the new word is in the list of possible intermediate words.
        Return the minimum number of operations required to change the starting word to the ending word.
        If it is not possible, return 0.

        Example:
            start = "hit", end = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
            ans = 5
            Explanation: "hit" -> "hot" -> "dot" -> "dog" -> "cog"

        We use a set to keep track of the words that we have visited and check if a new word is in the wordList or not.
        We use a queue to perform BFS. The queue contains the word and the number of operations required to reach that word.
        If during BFS, we encounter the ending word, we return the number of operations required to reach that word.
        Else, we continue BFS until the queue is empty.

        Now bruteforce to try out all possible characters in all possible positions of the word, i.e change the word in all possible ways.
        If the new word is in the wordList, then we add it to the queue and mark it as visited by removing it from the set.

        If we reach the end of BFS, then we return 0.

        Time: O(n*m*26), Space: O(n)
            Where n = number of words in wordList, m = length of word
*/

class Solution {
public:
    int ladderLength(const string& start, const string& end, const vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<pair<string, int>> q;

        st.erase(start);
        q.push({ start, 1 });

        while ( !q.empty() ) {
            auto [s, d] = q.front();
            q.pop();
            if ( s == end ) return d;

            for ( int i = 0; i < s.size(); i++ ) {
                char x = s[i];
                for ( char j = 'a'; j <= 'z'; j++ ) {
                    s[i] = j;
                    if ( st.count(s) ) {
                        st.erase(s);
                        q.push({ s, d + 1 });
                    }
                }
                s[i] = x;
            }
        }
        return 0;
    }
};

int main() {
    Solution s;
    vector<string> wordList = { "hot","dot","dog","lot","log","cog" };
    cout << s.ladderLength("hit", "cog", wordList) << endl;
    return 0;
}

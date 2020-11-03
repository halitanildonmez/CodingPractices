#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
using namespace std; // since cin and cout are both in namespace std, this saves some text
struct Node {
    Node* children[26];
    int substringCount = 0;
};
Node* root;
int sol = 0;
Node* createNode() {
    Node* ret = new Node;
    memset(ret->children, 0, sizeof(ret->children));
    return ret;
}
void add(string s) {
    Node* cur = root;
    for (int i = 0; i < s.size(); i++) {
        int index = s[i] - 'A';
        if (!cur->children[index]) {
            cur->children[index] = createNode();
        }
        cur = cur->children[index];
        cur->substringCount++;
    }
}
void dfs(Node* n, int d) {
    if (n == NULL)
        return;
    sol += n->substringCount / d;
    for (int i = 0; i < 26; i++) {
        if (n->children[i]) {
            dfs(n->children[i], d);
        }
    }
}
void solve(int n) {
    root = createNode();
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add(s);
    }
}
int main() {
  int t, n, m;
  cin >> t; // read t. cin knows that t is an int, so it reads it as such.
  for (int i = 1; i <= t; ++i) {
    cin >> n >> m; // read n and then m.
    solve(n);
    dfs(root, m);
    cout << "Case #" << i << ": " << sol << endl;
    sol = 0;
    root = NULL;
  }
  return 0;
}
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 200100
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname "KPHIT"
#define bit(S, i) (((S) >> (i)) & 1)
using namespace std;

struct Node {
    int Next[2];
    bool isLeaf;
    int p, link, go[2], pch;
};

Node Trie[N];
int sz;

void Init() {
    Trie[0].p = Trie[0].link = -1;
    memset(Trie[0].Next, -1, sizeof (Trie[0].Next));
    memset(Trie[0].go, -1, sizeof(Trie[0].go));
    sz = 0;
}

void AddString(string &s) {
    int now = 0;
    for (char c : s) {
        int id = c - '0';
        if (Trie[now].Next[id] == -1) {
            sz++;
            memset(Trie[sz].Next, -1, sizeof (Trie[sz].Next));
            memset(Trie[sz].go, -1, sizeof (Trie[sz].go));
            Trie[sz].link = -1;
            Trie[sz].p = now;
            Trie[sz].pch = id;
            Trie[now].Next[id] = sz;
        }
        now = Trie[now].Next[id];
    }
    Trie[now].isLeaf = true;
}

int Go(int u, int c);

int GetLink(int u) {
    if (Trie[u].link == -1) {
        if (u == 0 || Trie[u].p == 0) Trie[u].link = 0;
        else {
            Trie[u].link = Go(GetLink(Trie[u].p), Trie[u].pch);
        }
    }
    return Trie[u].link;
}

int Go(int u, int c) {
    if (Trie[u].go[c] == -1) {
        if (Trie[u].Next[c] != -1) {
            Trie[u].go[c] = Trie[u].Next[c];
        } else {
            Trie[u].go[c] = (u == 0) ? 0 : Go(GetLink(u), c);
        }
    }
    return Trie[u].go[c];
}

string seed;

void Backtrack(int u, string &s) {
    if (u == (int)seed.size()) {
    //    DEBUG(s);
        AddString(s); return;
    }
    if (seed[u] == '1') {
        s.push_back('1');
        Backtrack(u + 1, s);
        s.pop_back();
    }
    else {
        REP(i, 2) {
            s.push_back('0' + i);
            Backtrack(u + 1, s);
            s.pop_back();
        }
    }
}
int n;
double dp[55][N][2], p;
int used[55][N][2];

double Cal(int u, int node, bool ok) {
    if (Trie[node].isLeaf) ok = true;
    if (u == n)
        return ok ? 1 : 0;
    if (used[u][node][ok]) return dp[u][node][ok];
    used[u][node][ok] = 1;
    REP(i, 2) {
        dp[u][node][ok] += Cal(u + 1, Go(node, i), ok) * (i ? p : (1.0 - p));
    }
    return dp[u][node][ok];
}

int main() {
        freopen(taskname".inp","r",stdin);
        freopen(taskname".out","w",stdout);
    IO;
    int k;
    cin >> n >> k >> p;
    string s;
    Init();
    REP(i, k) {
        cin >> seed;
        Backtrack(0, s);
    }
    cout << fixed << setprecision(5) << Cal(0, 0, 0);
}

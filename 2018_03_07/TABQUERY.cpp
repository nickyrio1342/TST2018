#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<= b; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define DEBUG(x) { cerr << #x << " = " << x << endl; }
#define Arr(A, l, r) { cerr << #A  << " = "; FOR(_, l, r) cerr << A[_] << ' '; cerr << endl; }
#define N 1000000002
#define pp pair<int, int>
#define next __next
#define prev __prev
#define __builtin_popcount __builtin_popcountll
#define bit(S, i) (((S) >> i) & 1)
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);

template<typename T> inline void read(T &x) {
    x = 0;
    bool neg = false;
    char c;
    while (!isdigit(c = getchar()) && c != '-') ;
    if (c == '-') {
        neg = true; c = getchar();
    }
    while (true) {
        x*= 10; x += c - '0';
        if (!isdigit(c = getchar())) break;
    }
    if (neg) x = -x;
}
template<typename T> inline void write(T x) {
    if (x < 0) { putchar('-'); write(-x); return; }
    if (x < 10) putchar('0' + x);
    else {
        write(x/10); putchar('0' + x%10);
    }
}

template<typename T> inline void writeln(T x) {
    write(x); putchar('\n');
}
using namespace std;

const int MOD = 1e9;

struct Trie {
    Trie * child[2];
    int val;

    Trie() {
        child[0] = child[1] = NULL;
        val = 0;
    }

};

void UpTrie(Trie * root, int x, int val) {
    Trie * p = root;
    FORD(i, 29, 0) {
        int id = bit(x, i);
        if (!p -> child[id]) p -> child[id] = new Trie();
        p = p -> child[id];
        p -> val += val;
    }
}

int GetTrie(Trie * root, int x) {
    Trie * p = root;
    int ans = 0;
    FORD(i, 29, 0) {
        int id = bit(x, i);
        if (id && p -> child[0] != NULL) ans += p -> child[0] -> val;
        if (!p -> child[id]) return ans;
        p = p -> child[id];
        if (!i) ans += p -> val;
    }
    return ans;
}
map<int, Trie* >BIT;

void UpBIT(int u, int y, int val) {
    for (; u < N; u += u & -u) {
        if (BIT.find(u) == BIT.end()) BIT[u] = new Trie();
        UpTrie(BIT[u], y, val);
    }
}

int GetBIT(int u, int y1, int y2) {
    int ans = 0;
    for(; u > 0; u -= u & -u) {
        if (BIT.find(u) == BIT.end()) continue;
        ans += GetTrie(BIT[u], y2) - GetTrie(BIT[u], y1 - 1);
    }
    return ans;
}

int Get(int x1, int y1, int x2, int y2) {
    return GetBIT(x2, y1, y2) - GetBIT(x1 - 1, y1, y2);
}
int bef;

int f(int x) {
    return x + bef < MOD ? x + bef : x + bef - MOD;
}
int main() {
    //IO;
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    #endif // NERO
    bef = 0;
    int q;
    read(q);
    while (q--) {
        int type;
        read(type); 
        if (type == 1) {
            int x, y, val;
            read(x); read(y); read(val);
            x = f(x), y = f(y);
            UpBIT(x + 1, y + 1, val);
        }
        else {
            int x1, y1, x2, y2;
            read(x1); read(y1); read(x2); read(y2); 
            x1 = f(x1), x2 = f(x2), y1 = f(y1), y2 = f(y2);
            int now = Get(x1 + 1, y1 + 1, x2 + 1, y2 + 1);
            writeln(now);
            bef = f(abs(now));
        }
    }
}

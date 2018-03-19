#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<= b; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define DEBUG(x) { cerr << #x << " = " << x << endl; }
#define Arr(A, l, r) { cerr << #A  << " = "; FOR(_, l, r) cerr << A[_] << ' '; cerr << endl; }
#define N 200505
#define pp pair<long long, int>
#define next __next
#define prev __prev
#define __builtin_popcount __builtin_popcountll
#define bit(S, i) (((S) >> i) & 1)
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);

using namespace std;

string st;
int n, k, a[N][4];

int idx(char c) {
    if (c == 'A') return 1;
    if (c == 'C') return 0;
    if (c == 'T') return 2;
    return 3;
}
set<vector<int> > total;

int main() {
    IO;
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    #else
    freopen("EVOLUTION.inp","r",stdin);
    freopen("EVOLUTION.out","w",stdout);
    #endif // NERO
    cin >> n >> k >> st;
    st = '~' + st;
    FOR(i, 1, n) {
        REP(j, 4) a[i][j] = a[i - 1][j];
        a[i][idx(st[i])]++;
    }
    FOR(i, 1, n - k + 1) {
        vector<int> cnt(4, 0);
        REP(j, 4) cnt[j] = a[i + k - 1][j] - a[i - 1][j];
        total.insert(cnt);
    }
    cout << total.size();
}

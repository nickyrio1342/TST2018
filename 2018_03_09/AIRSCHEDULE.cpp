#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 505
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname ""
#define bit(S, i) (((S) >> (i)) & 1)
using namespace std;

struct HopcroftKarp{
    vector<int> d, match;
    int n;
    vector< vector<int> > e;
    const int inf = 1e9, nil = 0;

    void reset(int _n) {
        n = _n;
        e.clear(); e.resize(n + n + 1);
        d.clear(); d.resize(n + n + 1);
        match = d;
    }

    void addEdge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }

    int Matching() {
        int matching = 0;
        while (bfs()) {
            FOR(i, 1, n) if (match[i] == nil && dfs(i))
                matching++;
        }
        return matching;
    }
private:
    queue<int> q;
    bool bfs() {
        FOR(i, 1, n) if (match[i] == nil) {
            q.push(i);
            d[i] = 0;
        } else d[i] = inf;
        d[nil] = inf;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : e[u]) {
                if (d[match[v]] == inf) {
                    d[match[v]] = d[u] + 1;
                    q.push(match[v]);
                }
            }
        }
        return d[nil] != inf;
    }

    bool dfs(int u) {
        if (u != nil) {
            for (int v : e[u]) {
                if (d[match[v]] == d[u] + 1) {
                    if (dfs(match[v])) {
                        match[u] = v;
                        match[v] = u;
                        return true;
                    }
                }
            }
            d[u] = inf;
            return false;
        }
        return true;
    }
}HK;

int c[N][N], org[N][N];
int m, n, p[N], s[N], f[N], t[N];

void Floyd() {
    FOR(i, 1, n) FOR(j, 1, n) {
        org[i][j] = c[i][j];
        if (i != j) c[i][j] += p[j];
    }
    FOR(k, 1, n) FOR(i, 1, n) FOR(j, 1, n) {
        c[i][j] = min(c[i][j], c[i][k] + c[k][j]);
    }
}

int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    #else
    freopen("AIRSCHEDULE.inp","r",stdin);
    freopen("AIRSCHEDULE.out","w",stdout);
    #endif //NERO
    IO;
    cin >> n >> m;
    FOR(i, 1, n) cin >> p[i];
    FOR(i, 1, n) FOR(j, 1, n) cin >> c[i][j];
    Floyd();
    FOR(i, 1, m) {
        cin >> s[i] >> f[i] >> t[i];
    }
    HK.reset(m);
    FOR(i, 1, m) FOR(j, 1, m) if (i != j && t[i] <= t[j]) {
        if (t[i] + org[s[i]][f[i]] + p[f[i]] + c[f[i]][s[j]] <= t[j]) {
            HK.addEdge(i, j + m);
     //       DEBUG(i);DEBUG(j);
        }
    }
    //FOR(i, 1, n) Arr(c[i], 1, n);return 0;
    cout << m - HK.Matching();
}

//https://www.acmicpc.net/problem/12823
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 100100
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname ""
#define bit(S, i) (((S) >> (i)) & 1)
using namespace std;

int n;
int IN[N], f[N], g[N];
vector<int> e[N], rev_e[N], level[N];

void Solve() {
    queue<int> q;
    FOR(i, 1, n) if (IN[i] == 0) { q.push(i); f[i] = 1; }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        level[f[u]].push_back(u);
        for (int v : e[u]) {
            IN[v]--;
            f[v] = max(f[v], f[u] + 1);
            if (IN[v] == 0) q.push(v);
        }
    }
    FOR(u, 1, n) {
        g[u] = n + 1;
        for (int v : e[u]) {
            g[u] = min(g[u], f[v]);
        }
    }
    vector<int> res;
    int MAX = 0;
    FOR(i, 1, n) {
        //DEBUG(i);
        if (level[i].size() == 1) {
            int u = level[i][0];
            if (MAX <= f[u]) res.push_back(u);
        }
        for (int u : level[i]) {
            //DEBUG(u);
            MAX = max(MAX, g[u]);
        }
        //DEBUG(MAX);
    }
    sort(res.begin(), res.end());
    cout << res.size() << endl;
    for (int x : res) cout << x << ' ';
}
int mark[N], cnt;
void dfs(int u) {
    mark[u] = 1;
    cnt++;
    for (int v : e[u]) if (!mark[v]) {
        dfs(v);
    }
    for (int v : rev_e[u]) if (!mark[v]) {
        dfs(v);
    }
}
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    clock_t stime = clock();
    #endif //NERO
    IO;
    int m;
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        rev_e[v].push_back(u);
        IN[v]++;
    }
    cnt = 0;
    dfs(1);
    if (cnt != n) {
        cout << 0; return 0;
    }
    Solve();
    #ifdef NERO
    clock_t etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.";
    #endif // NERO
}

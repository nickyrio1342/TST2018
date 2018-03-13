#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 1001000
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname ""
#define bit(S, i) (((S) >> (i)) & 1)
using namespace std;

int n, a, b;
vector<int> e[N], ver;
int p[N];

void dfs(int u) {
    for (int v : e[u]) if (v != p[u]) {
        p[v] = u;
        dfs(v);
    }
}
int dp[N], mark[N];

int dfs2(int u, int ban, int p) {
    if (!mark[u] && dp[u] != -1) return dp[u];
    vector<int> tmp;
    for (int v : e[u]) if (v != p && v != ban) {
        tmp.push_back(dfs2(v, ban, u));
    }
    sort(tmp.begin(), tmp.end());
    int MAX = 0, cnt = 0;
    while (tmp.empty() == false) {
        MAX = max(MAX, tmp.back() + (++cnt));
        tmp.pop_back();
    }
    dp[u] = MAX;
    return MAX;
}
int f(int id) {
    return dfs2(a, ver[id - 1], -1) - dfs2(b, ver[id], -1);
}

int g(int id) {
    return max(dfs2(a, ver[id - 1], -1), dfs2(b, ver[id], -1));
}
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    #endif //NERO
    scanf("%d %d %d", &n, &a, &b);
    FOR(i, 2, n) {
        int u, v;
        scanf("%d %d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    p[a] = -1;
    dfs(a);
    int v = b;
    FOR(i, 1, n) dp[i] = -1;
    while (v != -1) {
        mark[v] = true;
        ver.push_back(v);
        v = p[v];
    }
    int l = 1, r = ver.size() - 1, cur = -1;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (f(m) >= 0) {
            cur = m;
            l = m + 1;
        } else r = m - 1;
    }
    int ans = g(cur);
    if (cur != ver.size() - 1) ans = min(ans, g(cur + 1));
    printf("%d", ans);
}

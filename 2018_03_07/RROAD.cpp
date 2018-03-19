#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<= b; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define DEBUG(x) { cerr << #x << " = " << x << endl; }
#define Arr(A, l, r) { cerr << #A  << " = "; FOR(_, l, r) cerr << A[_] << ' '; cerr << endl; }
#define N 1005
#define pp pair<long long, int>
#define next __next
#define prev __prev
#define __builtin_popcount __builtin_popcountll
#define bit(S, i) (((S) >> i) & 1)
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);

using namespace std;

int n, m;
vector<pp> e[N];
int d[N];
priority_queue<pp> heap;

void Dijkstra(int s, int ban) {
    FOR(i, 1, n) d[i] = 1e9;
    heap.push(pp(d[s] = 0, s));
    while (!heap.empty()) {
        int u = heap.top().second;
        int dist = -heap.top().first;
        heap.pop();
        if (dist != d[u]) continue;
        for (pp tt : e[u]) {
            int v = tt.first, c = tt.second;
            if (u == s && v == ban) continue;
            if (d[v] > d[u] + c) {
                heap.push(pp(-(d[v] = d[u] + c), v));
            }
        }
    }
}

int main() {
    IO;
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    #endif // NERO
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, c;
        cin >> u >> v >> c;
        e[u].push_back(pp(v, c));
        e[v].push_back(pp(u, c));
    }
    double ans = 1.0;
    if (m == 1) ans = -1;
    FOR(u, 1, n) {
        Dijkstra(u, -1);
        vector<pp> Check;
        for (pp tt : e[u]) {
            int v = tt.first, c = tt.second;
            if (d[v] == d[u] + c) Check.push_back(pp(v, c));
        }
        for (pp tt : Check) {
            int v = tt.first, c = tt.second;
            if (v < u) continue;
            Dijkstra(u, v);
            if (d[v] == 1e9) continue;
            ans = max(ans, 1.0 * d[v] / c);
        }
    }
    cout << fixed << setprecision(10) << ans;
}

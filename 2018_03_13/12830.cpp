//https://www.acmicpc.net/problem/12830
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 51000
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname ""
#define bit(S, i) (((S) >> (i)) & 1)
#define esp 1e-7
using namespace std;

void Max(double &a, double b) { a = a > b ? a : b; }
int n, k;
double MAX[N];
int visited[N];
bool skipped[N];
int nChild[N];
vector<int> e[N];
vector<pp> ee[N];

void dfsCentroid(int u, int p) {
    nChild[u] = 1;
    for (int v : e[u]) if (v != p && !skipped[v]) {
        dfsCentroid(v, u);
        nChild[u] += nChild[v];
    }
}
int findCentroid(int u, int p, int cntNode) {
    for (int v : e[u]) if (v != p && !skipped[v]) {
        if (nChild[v] * 2 > cntNode) return findCentroid(v, u, cntNode);
    }
    return u;
}

double subtract;
bool dfsQuery(int u, int p, int depth, double cost) {
    visited[u] = 1;
    if (cost + MAX[max(0, k - depth)] >= -esp) return true;
    for (pp tt : ee[u]) {
        int v = tt.first;
        double c = 1.0 * tt.second - subtract;
        if (v != p && !skipped[v]) {
            if (dfsQuery(v, u, depth + 1, cost + c)) return true;
        }
    }
    return false;
}

int dfsUpdate(int u, int p, int depth, double cost) {
    // Return max depth
    int maxdepth = depth;
    Max(MAX[depth], cost);
    for (pp tt : ee[u]) {
        int v = tt.first;
        double c = 1.0 * tt.second - subtract;
        if (v != p && !skipped[v]) {
            int d = dfsUpdate(v, u, depth + 1, cost + c);
            if (maxdepth < d) maxdepth = d;
        }
    }
    return maxdepth;
}

bool Ok(double _subtract) {
    subtract = _subtract;
    FOR(i, 1, n) skipped[i] = 0;
    while (true) {
        bool change = false;
        FOR(i, 1, n) MAX[i] = -1e18, visited[i] = 0;
        FOR(u, 1, n) if (!skipped[u] && !visited[u]) {
            change = true;
            int mx = 0;
            dfsCentroid(u, -1);
            int centroid = findCentroid(u, -1, nChild[u]);
            MAX[0] = 0;
            for (pp tt : ee[centroid]) {
                int v = tt.first;
                if (skipped[v]) continue;
                double c = 1.0 * tt.second - subtract;
                if (dfsQuery(v, centroid, 1, c)) return true;
                int depth = dfsUpdate(v, centroid, 1, c);
                FORD(j, depth - 1, 0) Max(MAX[j], MAX[j + 1]);
                if (depth > mx) mx = depth;
            }
            skipped[centroid] = 1;
            FOR(i, 1, mx) MAX[i] = -1e18;
        }
        if (!change) return false;
    }
}

void Solve() {
    double l = 0, r = 1e6;
    REP(loop, 100) {
        if(r - l <= esp) break;
        double m = (l + r) / 2;
        if (Ok(m)) l = m; else r = m;
    }
    cout << fixed << setprecision(10) << l;
}

int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    double stime = clock();
    #endif //NERO
    IO;
    cin >> n >> k;
    FOR(i, 2, n) {
        int u, v, c;
        cin >> u >> v >> c;
        e[u].push_back(v);
        e[v].push_back(u);
        ee[u].push_back(pp(v, c));
        ee[v].push_back(pp(u, c));
    }
    Solve();
    #ifdef NERO
    double etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.\n";
    #endif // NERO
}

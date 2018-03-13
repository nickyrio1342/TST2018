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

int f[N];
int root(int u) { return f[u] < 0 ? u : (f[u] = root(f[u])); }
bool Union(int a, int b) {
    a = root(a), b = root(b);
    if (a == b) return false;
    int t = f[a] + f[b];
    if (f[a] > f[b]) swap(a, b);
    f[a] = t;
    f[b] = a;
    return true;
}
struct Edge {
    int id;
    int cost;

    Edge() {}
    Edge(int id, int cost): id(id), cost(cost) {}
    bool operator<(Edge a) {
        return cost < a.cost;
    }
};

Edge edge[N];
pp e[N], c[N];
int n, m;
int ans;
pp Kruskal(int c1, int c2) {
    REP(i, n) f[i] = -1;
    REP(i, m) edge[i] = Edge(i, c1 * c[i].first + c2 * c[i].second);
    sort(edge, edge + m);
    pp res = pp(0, 0);
    REP(i, m) {
        int id = edge[i].id;
        if (Union(e[id].first, e[id].second)) {
            res.first += c[id].first;
            res.second += c[id].second;
        }
    }
    return res;
}

set<int> used;
void Cal(pp A, pp B) {
    ans = min(ans, A.first * A.second);
    ans = min(ans, B.first * B.second);
    pp C = Kruskal(A.second - B.second, B.first - A.first);
    if (used.find(C.first) != used.end()) return;
    used.insert(C.first);
    if (C == A || C == B) return;
    Cal(A, C); Cal(C, B);
}

int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    clock_t stime = clock();
    #endif //NERO
    IO;
    cin >> n >> m;
    REP(i, m) {
        cin >> e[i].first >> e[i].second >> c[i].first >> c[i].second;
    }
    ans = 1e18;
    Cal(Kruskal(1, 0), Kruskal(0, 1));
    cout << ans;
    #ifdef NERO
    clock_t etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.";
    #endif // NERO
}

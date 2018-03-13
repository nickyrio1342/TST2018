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
double ans;

void Solve(int u, int p, long long c, int cnt) {
    if (cnt >= k) {
        ans = max(ans, 1.0 * c / cnt);
    }
    for (pp tt : ee[u]) {
        int v = tt.first;
        int w = tt.second;
        if (v != p) Solve(v, u, c + w, cnt + 1);
    }
}
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.ans","w",stdout);
    double stime = clock();
    #endif //NERO
    IO;
    cin >> n >> k;
    FOR(i, 2, n) {
        int u, v, c;
        cin >> u >> v >> c;
        ee[u].push_back(pp(v, c));
        ee[v].push_back(pp(u, c));
    }
    ans = 0;
    FOR(u, 1, n) Solve(u, -1, 0, 0);
    cout << fixed << setprecision(10) << ans << endl;
    #ifdef NERO
    double etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.\n";
    #endif // NERO
}
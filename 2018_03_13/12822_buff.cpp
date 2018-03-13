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

int n;
long long x[N], d[N], c[N], ans;
bool visited[N];

void Try(int u, long long xx, long long cc, long long t) {
    if (u == n) {
        ans = min(ans, cc);
        return;
    }
    FOR(i, 1, n) if (!visited[i]) {
        visited[i] = 1;
        Try(u + 1, x[i], c[i] + cc + (t + abs(xx - x[i])) * d[i], (t + abs(xx - x[i])));
        visited[i] = 0;
    }
}
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.ans","w",stdout);
    double stime = clock();
    #endif //NERO
    IO;
    cin >> n >> x[0];
    FOR(i, 1, n) cin >> x[i] >> c[i] >> d[i];
    ans = 1e18;
    Try(0, x[0], 0, 0);
    cout << ans;
    #ifdef NERO
    double etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.\n";
    #endif // NERO
}

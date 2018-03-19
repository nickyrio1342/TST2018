#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 1001000
#define pp pair<double, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname "AIRCRAFT"
#define bit(S, i) (((S) >> (i)) & 1)
using namespace std;

    double P[N];
    int cnt[N];
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    double stime = clock();
    #else
        freopen(taskname".inp","r",stdin);
        freopen(taskname".out","w",stdout);
    #endif //NERO
    IO;
    int n, m;
    double p;
    priority_queue<pp> heap;
    cin >> n >> m >> p;
    FOR(i, 1, n) cin >> P[i];
    m -= n;
    FOR(i, 1, n) heap.push(pp(P[i], i));
    while (m--) {
        pp u = heap.top(); heap.pop();
        cnt[u.second]++;
        u.first = u.first * (1.0 - p);
        heap.push(u);
    }
    FOR(i, 1, n) cout << cnt[i] + 1 << ' ';
    #ifdef NERO
    double etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.\n";
    #endif // NERO
}

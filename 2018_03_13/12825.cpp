//https://www.acmicpc.net/problem/12825
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

int n, p[N], MAX[N];
set<int> tab;

int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    clock_t stime = clock();
    #endif //NERO
    IO;
    cin >> n;
    FOR(i, 1, n) cin >> p[i];
    FOR(i, 1, n) MAX[i] = max(MAX[i - 1], p[i]);
    tab.insert(p[n]);
    int mark = n - 2;
    FORD(i, n - 1, 1) if (p[i] < p[i + 1]) {
        mark = i - 1; break;
    }
    if (mark > n - 2) mark = n - 2;
    tab.clear();
    FORD(i, n, mark + 1) tab.insert(p[i]);
    p[mark + 1] = *tab.upper_bound(p[mark + 1]);
    tab.erase(p[mark + 1]);
    int last = n;
    int M = max(MAX[mark], p[mark + 1]);
    while (!tab.empty() && *tab.rbegin() > M) {
        p[last] = *tab.rbegin();
        tab.erase(p[last]);
        last--;
    }
    mark += 2;
    while (!tab.empty()) {
        p[mark] = *tab.rbegin();
        tab.erase(p[mark]);mark++;
    }
    FOR(i, 1, n) cout << p[i] << ' ';
    #ifdef NERO
    clock_t etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.";
    #endif // NERO
}

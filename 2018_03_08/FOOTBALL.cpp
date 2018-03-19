#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 5001
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define taskname ""
#define bit(S, i) (((S) >> (i)) & 1)

using namespace std;

int n, k, a[N][N];
int res[N];
void solve() {
    int l, r;
    cin >> l >> r;
    if (l == r) {
        cout << 1 << ' ' << l << endl;
        return;
    }
    res[0] = l;
    FOR(i, l + 1, r) {
        res[i - l] = i;
        int j = i - l;
        while (j && a[res[j]][res[j - 1]]) {
            swap(res[j], res[j - 1]);
            j--;
        }
    }
    cout << r - l + 1 << ' ';
    REP(i, r - l + 1) cout << res[i] << ' '; cout << endl;
}
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    #else
    freopen("FOOTBALL.inp","r",stdin);
    freopen("FOOTBALL.out","w",stdout);
    #endif //NERO
    IO;
    cin >> n >> k;
    FOR(i, 1, n) FOR(j, 1, n) cin >> a[i][j];
    while (k--) solve();
}

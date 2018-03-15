#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 111
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname "P01"
#define bit(S, i) (((S) >> (i)) & 1)
using namespace std;

int n;
double p;
int used[N][N];
double dp[N][N];

double cal(int u, int cnt1) {
    if (u == 0) {
        if (cnt1 == 0) return 1;
        return 0;
    }
    if (used[u][cnt1]) return dp[u][cnt1];
    used[u][cnt1] = 1;
    if (cnt1 > 0) dp[u][cnt1] += cal(u - 1, cnt1 - 1) * p;
    if (cnt1 != u) dp[u][cnt1] += cal(u - 1, cnt1) * (1.0 - p);
    return dp[u][cnt1];
}
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    double stime = clock();
    #else 
        freopen("taskname.inp","r",stdin);
        freopen("taskname.out","w",stdout);
    #endif //NERO
    IO;
    cin >> n >> p;
    double ans = 0;
    FOR(i, 1, n) ans += cal(n, i) * i;
    cout << fixed << setprecision(5) <<ans;
    #ifdef NERO
    double etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.\n";
    #endif // NERO
}

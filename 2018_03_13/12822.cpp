//https://www.acmicpc.net/problem/12822
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 2020
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname ""
#define bit(S, i) (((S) >> (i)) & 1)
using namespace std;

struct Point {
    long long x, d;
    bool operator<(Point a) {
        return x < a.x;
    }
}p[N];

int n;
long long pos, x[N], sumD[N], dp[N][N][2];
long long Min(long long &a, long long b) { a = a > b ? b : a; }
const long long inf = 1e18;

int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    clock_t stime = clock();
    #endif //NERO
    IO;
    long long res = 0;
    cin >> n >> pos;
    FOR(i, 1, n) {
        long long c;
        cin >> p[i].x >> c >> p[i].d;
        res += c;
    }
    sort(p + 1, p + n + 1);
    FOR(i, 1, n) {
        x[i] = p[i].x;
        sumD[i] = sumD[i - 1] + p[i].d;
    }
    int xx = lower_bound(x + 1, x + n + 1, pos) - x;
    memset(dp, 60, sizeof dp);
    dp[xx][xx][1] = sumD[n] * (x[xx] - pos);
    dp[xx - 1][xx - 1][0] = sumD[n] * (pos - x[xx - 1]);
    FORD(i, xx, 1) FOR(j, xx - 1, n) if (i < j) {
        if (dp[i + 1][j][0] != inf) {
            long long val = dp[i + 1][j][0] + (sumD[n] - sumD[j] + sumD[i]) * (x[i + 1] - x[i]);
            Min(dp[i][j][0], val);
        }
        if (dp[i + 1][j][1] != inf) {
            long long val = dp[i + 1][j][1] + (sumD[n] - sumD[j] + sumD[i]) * (x[j] - x[i]);
            Min(dp[i][j][0], val);
        }
        if (dp[i][j - 1][0] != inf) {
            long long val = dp[i][j - 1][0] + (x[j] - x[i]) * (sumD[n] - sumD[j - 1] + sumD[i - 1]);
            Min(dp[i][j][1], val);
        }
        if (dp[i][j - 1][1] != inf) {
            long long val = dp[i][j - 1][1] + (x[j] - x[j - 1]) * (sumD[n] - sumD[j - 1] + sumD[i - 1]);
            Min(dp[i][j][1], val);
        }
    }
    cout << min(dp[1][n][0], dp[1][n][1]) + res << endl;
    #ifdef NERO
    clock_t etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.\n";
    #endif // NERO
}

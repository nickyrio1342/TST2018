#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 2001
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname ""
#define bit(S, i) (((S) >> (i)) & 1)
#define clock_t double
using namespace std;

const int dd[8] = {1, 2, -1, 2, 1, -2, -1, -2};
const int cc[8] = {2, 1, 2, -1, -2, 1, -2, -1};
int n, m, k;

struct Point {
    int x, y, id;
    Point() {}
    Point(int x, int y, int id): x(x), y(y), id(id) {}
    bool inside() { return x > 0 && y > 0 && x <= m && y <= n; }
}tot, ma;

queue<Point> q;
int f[N][N][2], a[N], b[N];

int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    clock_t stime = clock();
    #endif //NERO
    scanf("%d %d %d", &m, &n, &k);
    scanf("%d %d", &tot.x, &tot.y);
    FOR(i, 1, m) FOR(j, 1, n) REP(z, 2) f[i][j][z] = -1;
    REP(i, k) {
        scanf("%d %d", &ma.x, &ma.y);
        ma.id = 0;
        f[ma.x][ma.y][0] = 0;
        q.push(ma);
    }
    while (!q.empty()) {
        Point u = q.front(); q.pop();
        REP(i, 8) {
            Point v(u.x + dd[i], u.y + cc[i], u.id ^ 1);
            if (!v.inside()) continue;
            if (f[v.x][v.y][v.id] == -1) {
                f[v.x][v.y][v.id] = f[u.x][u.y][u.id] + 1;
                q.push(v);
            }
        }
    }
    FOR(i, tot.x + 1, m) a[i] = i - tot.x;
    b[m] = a[m];
    FORD(i, m - 1, 1) b[i] = b[i + 1] + 1;
    a[1] = b[1];
    int step = m + m - 2;
    FOR(i, 2, tot.x) a[i] = a[i - 1] + 1;
    int ans = 1e9;
    FOR(i, 1, m) {
        REP(j, 2) {
            if (f[i][tot.y][j] != -1) {
                if (a[i] % 2 == j) {
                    int TIME = max(0, (f[i][tot.y][j] - a[i])) / step * step + a[i];
                    if (TIME < f[i][tot.y][j]) TIME += step;
                    ans = min(ans, TIME);
                }
                if (b[i] % 2 == j) {
                    int TIME = max(0, (f[i][tot.y][j] - b[i])) / step * step + b[i];
                    if (TIME < f[i][tot.y][j]) TIME += step;
                    ans = min(ans, TIME);
                }
            }
        }
    }
    if (ans == 1e9) ans = -1;
    printf("%d", ans);
    #ifdef NERO
    clock_t etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.";
    #endif // NERO
}

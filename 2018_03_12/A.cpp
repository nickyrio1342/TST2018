#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 201000
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname ""
#define bit(S, i) (((S) >> (i)) & 1)
using namespace std;

int BLOCK_SIZE;
struct Query {
    int id, l, r;
    bool operator<(Query b) {
        return b.r / BLOCK_SIZE != r / BLOCK_SIZE ? r / BLOCK_SIZE < b.r / BLOCK_SIZE : l > b.l;
    }
}que[N];

int n, q, a[N], Chain[N], nChain, BEF[N];
map<int, int> bef[N];
vector<int> Belong[N]; // Store id segment [l, r]
int R[N], L[N], res[N];

int f[N];
int Buffalo(int l, int r) {
    FOR(i, l - 1, r) f[i] = 0;
    int ans = 0;
    FOR(i, l, r) if (Chain[i] != -1 && BEF[i] + 1 >= l) {
        f[i] = f[BEF[i]] + i - BEF[i];
        ans = max(ans, f[i]);
    }
    return ans;
}
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    double stime = clock();
    #endif //NERO
    IO;
    cin >> n >> q;
    BLOCK_SIZE = 300;
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 0, n) Chain[i] = -1;
    FOR(i, 2, n) {
        if (a[i] == -a[i - 1]) {
            int c;
            if (i > 2 && Chain[i - 2] != -1) c = Chain[i - 2];
            else c = ++nChain;
            Belong[i - 1].push_back(c);
            if (i > 2) bef[c][a[i - 2]] = i - 2;
            Chain[i] = c;
            BEF[i] = i - 2;
        } else {
            if (Chain[i - 1] == -1) continue;
            int c = Chain[i - 1];
            if (bef[c].find(-a[i]) == bef[c].end()) continue;
            int pos = bef[c][-a[i]];
            BEF[i] = pos - 1;
            if (Chain[pos - 1] == -1) c = ++nChain;
            else c = Chain[pos - 1];
            Belong[pos].push_back(c);
            if (pos > 1) bef[c][a[pos - 1]] = pos - 1;
            Chain[i] = c;
        }
    }
  //  Arr(Chain, 1, n);
    REP(i, q) cin >> que[i].l >> que[i].r;
    REP(i, q) que[i].id = i;
    sort(que, que + q);
    int LEFT, RIGHT, MAX;
    REP(i, q) {
        int l = que[i].l, r = que[i].r, id = que[i].id;
        if (!i || que[i].r / BLOCK_SIZE != que[i - 1].r / BLOCK_SIZE) {
            MAX = 0;
            LEFT = (que[i].r / BLOCK_SIZE) * BLOCK_SIZE;
            RIGHT = LEFT - 1;
            FOR(i, 1, nChain) R[i] = 0, L[i] = n + 1;
        }
        if (l / BLOCK_SIZE == r / BLOCK_SIZE) res[id] = Buffalo(l, r);
        else {
            while (LEFT > l) {
                --LEFT;
                if (Chain[LEFT] != -1 && R[Chain[LEFT]] == 0) R[Chain[LEFT]] = LEFT;
                for (int id : Belong[LEFT]) {
                    L[id] = LEFT;
                    MAX = max(MAX, R[id] - LEFT + 1);
                }
            }
            int MX = max(MAX, Buffalo(RIGHT + 1, r));
            while (r > RIGHT) {
                if (Chain[r] != -1 && L[Chain[r]] != n + 1) {
                    MX = max(MX, r - L[Chain[r]] + 1);
                }
                r--;
            }
            res[id] = MX;
        }

    }
    REP(i, q) cout << res[i] << '\n';
    #ifdef NERO
    double etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.";
    #endif // NERO
}

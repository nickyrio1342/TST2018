#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 501000
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname ""
#define bit(S, i) (((S) >> (i)) & 1)
template<typename T> inline void read(T &x) {
    x = 0;
    char c;
    while (!isdigit(c = getchar())) ;
    while (true) {
        x *= 10;
        x += c - '0';
        if (!isdigit(c = getchar())) return;
    }
}
using namespace std;

int n, m, d, a[N];
int GCD[N][20], lg[N];

void BuildRMQGCD() {
    FOR(i, 1, m) GCD[i][0] = a[i];
    FOR(j, 1, 19) FOR(i, 1, n) if (i + (1 << j) - 1 <= n)
        GCD[i][j] = __gcd(GCD[i][j - 1], GCD[i + (1 << (j - 1))][j - 1]);
}
int gcdRange(int l, int r) {
    int d = lg[r - l + 1];
    return __gcd(GCD[l][d], GCD[r + 1 - (1 << d)][d]);
}

long long IT[N << 2];
void Up(int k, int l, int r, int u, long long val) {
    if (l == r) {
        IT[k] = val;return;
    }
    int m = (l + r) >> 1;
    if (u <= m) Up(k << 1, l, m, u, val);
    else Up(k << 1 | 1, m + 1, r, u, val);
    IT[k] = max(IT[k << 1], IT[k << 1 | 1]);
}

long long Query(int k, int l, int r, int u, int v) {
    if (l > v || r < u) return 0;
    if (u <= l && r <= v) return IT[k];
    int m = (l + r) >> 1;
    return max(Query(k << 1, l, m, u, v), Query(k << 1 | 1, m + 1, r, u, v));
}

vector<pp> st; // pair<GCD, position>
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    #else
    freopen("GCDSUM.inp","r",stdin);
    freopen("GCDSUM.out","w",stdout);
    #endif //NERO
    read(n); read(m); read(d);
    FOR(i, 1, n) lg[i] = log2(i);
    int bef = 0;
    FOR(i, 1, n) {
        int k; read(k);
        k += bef;
        FOR(i, bef + 1, k) read(a[i]);
        bef = k;
    }
    BuildRMQGCD();
    long long ans = 0;
    FOR(i, 1, m) {
        int now = a[i];
        st.push_back(pp(a[i], i));
        int sz = (int)st.size() - 2;
        FORD(ii, sz, 0) {
            if (now % st[ii].first == 0) {
                FORD(jj, sz + 1, ii + 1) {
                    if (jj && st[jj].first == st[jj - 1].first)
                        st.erase(st.begin() + jj);
                }
                break;
            }
            now = __gcd(now, st[ii].first);
            st[ii].first = now;
        }
        if (i < d) continue;
        long long val = gcdRange(1, i);
        st.push_back(pp(-1, i + 1));
        sz = st.size() - 1;
        REP(ii, sz) {
            int gcd = st[ii].first;
            int l = st[ii].second - 1, r = st[ii + 1].second - 2;
            if (l < d) l = d;
            if (i - r < d) r = i - d;
            if (l > r) continue;
            val = max(val, Query(1, 0, m, l, r) + gcd);
        }
        Up(1, 0, m, i, val);
        ans = val;
        st.pop_back();
     }
    printf("%lld", ans);
}

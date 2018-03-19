#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<= b; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define DEBUG(x) { cerr << #x << " = " << x << endl; }
#define Arr(A, l, r) { cerr << #A  << " = "; FOR(_, l, r) cerr << A[_] << ' '; cerr << endl; }
#define N 200505
#define pp pair<long long, int>
#define next __next
#define prev __prev
#define __builtin_popcount __builtin_popcountll
#define bit(S, i) (((S) >> i) & 1)
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);

using namespace std;

struct suffix {
    int id, Rank[2];
};
    bool cmp(suffix a, suffix b) {
        return a.Rank[0] == b.Rank[0] ? a.Rank[1] < b.Rank[1] : a.Rank[0] < b.Rank[0];
    }
struct SuffixArray {
    string st;
    int n;
    int sa[N], lcp[N];
    suffix suf[N];
    int pre[20][N];

    void reset(string _st) {
        st = _st;
        n = st.size();
    }

    void buildSA() {
        REP(i, n) pre[0][i] = st[i];
        for (int step = 1, gap = 1; gap < n; gap *= 2, ++step) {
            REP(i, n) {
                suf[i].id = i;
                suf[i].Rank[0] = pre[step - 1][i];
                suf[i].Rank[1] = (i + gap < n) ? pre[step - 1][i + gap] : -1;
            }
            sort(suf, suf + n, cmp);
            REP(i, n) {
                pre[step][suf[i].id] = (i > 0 && suf[i].Rank[0] == suf[i - 1].Rank[0]
                                && suf[i].Rank[1] == suf[i - 1].Rank[1]) ? pre[step][suf[i - 1].id] : i;
            }
        }
        REP(i, n) sa[i] = suf[i].id;
        Arr(sa, 0, n - 1);
    }
    int r[N];
    void buildLCP() {
        int k = 0;
        REP(i, n) r[sa[i]] = i;
        REP(i, n) {
            if (r[i] == n - 1) {
                k = 0; continue;
            }
            int j = sa[r[i] + 1];
            while(i + k < n && j + k < n && st[i + k] == st[j + k]) ++k;
            lcp[r[i]] = k;
            if (k) --k;
        }
    }

    int countDiffSub() {
        int ans = 0;
        REP(i, n) {
            ans += n - sa[i] - (i ? lcp[i - 1] : 0);
        }
        return ans;
    }
} SA;
int main() {
    IO;
    #ifdef NERO
    //freopen("test.inp","r",stdin);
    //freopen("test.out","w",stdout);
    #else
    freopen("SUBSTRING.inp","r",stdin);
    freopen("SUBSTRING.out","w",stdout);
    #endif // NERO
    string st;
    cin >> st;
    SA.reset(st);
    SA.buildSA();return 0;
    SA.buildLCP();
    cout << SA.countDiffSub();
}

#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 1001000
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define taskname ""
using namespace std;

string f[N];
int n, m;
string st;

typedef vector<long long> BigNum;
const long long MOD = 1e10;

void Fix(BigNum &c) {
    c.push_back(0);
    REP(i, (int)c.size() - 1) {
        c[i + 1] += c[i] / MOD;
        c[i] %= MOD;
    }
    while ((int) c.size() > 1 && c.back() == 0) c.pop_back();
}

BigNum operator+(BigNum a, BigNum b) {
    BigNum c; c.clear(); c.resize(max(a.size(), b.size()));
    REP(i, (int)min(a.size(), b.size())) c[i] = a[i] + b[i];
    if (a.size() < b.size()) {
        FOR(i, a.size(), (int)b.size() - 1) c[i] = b[i];
    }
    else {
        FOR(i, b.size(), (int)a.size() - 1) c[i] = a[i];
    }
    Fix(c);
    return c;
}
BigNum Change(int x) {
    BigNum c; c.clear(); c.push_back(x);
    return c;
}

void Print(BigNum a) {
    cout << a.back(); a.pop_back();
    FORD(i, a.size() - 1, 0) {
        long long base = 1e9;
        REP(j, 10) {
            cout << (a[i] / base) % 10 ;
        //    DEBUG((a[i] / base) % 10);
            base /= 10;
        }
    }
    cout << endl;
}
int k;

void Init() {
    k = -1;
    f[0] = '1';
    f[1] = '0';
    FOR(i, 2, 50) {
        f[i] = f[i - 1] + f[i - 2];
        if ((int)f[i - 1].size() >= 1e4) {
            return;
        }
    }
}
int cost(string s) {
    s = st + s;
   // DEBUG(s);
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    FOR(i, 1, n - 1) {
        z[i] = i <= r ? min(r - i + 1, z[i - l]) : 0;
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1; l = i;
        }
    }
    int cnt = 0;
    FOR(i, m, n - 1) if (z[i] >= m) cnt++;
    return cnt;
}
BigNum g[N], ans;

void Solve() {
    int k = -1;
    FOR(i, 1, n + 1) {
        if ((int)f[i - 1].size() >= m) {
            k = i; break;
        }
    }
    if (k == -1) {
        string res;
        for(char c : st) if (c == '0') res = res + f[n + 1];
        else res = res + f[n];
        cout << cost(res) << '\n';
    }
    else {
        int c0 = cost(f[k - 1]), c1 = cost(f[k]);
        g[k - 1] = Change(c0);
        g[k] = Change(c1);
        int c[2][2];
        //DEBUG(f[k]);
        //DEBUG(f[k - 1]);
        c[1][0] = cost(f[k] + f[k - 1]) - c0 - c1, c[0][1] = cost(f[k - 1] + f[k]) - c0 - c1;
        c[0][0] = cost(f[k - 1] + f[k - 1]) - c0 - c0, c[1][1] = cost(f[k] + f[k]) - c1 - c1;
        FOR(i, k + 1, n + 1) {
            g[i] = g[i - 1] + g[i - 2] + Change((i % 2 != k % 2) ? c[1][0] : c[0][1]);
            //Arr(g[i], 0, (int)g[i].size() - 1);
        }
        ans.clear();
        ans = g[n + '1' - st[0]];
 //       Arr(ans, 0, (int)ans.size() - 1);
        FOR(i, 1, m - 1) {
            if (k % 2 != n % 2)
                ans = ans + Change(c['1' - st[i - 1]]['1' - st[i]]) + g[n + '1' - st[i]];
            else {
                ans = ans + Change(c[st[i - 1] - '0'][st[i] - '0']) + g[n + '1' - st[i]];
            }
            //Arr(ans, 0, (int)ans.size() - 1);
        }
        Print(ans);
    }
}
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    #else
    freopen("VIRUS.inp","r",stdin);
    freopen("VIRUS.out","w",stdout);
    #endif //NERO
    IO;
    Init();
    while (cin >> n >> st) {
        n--;
        m = st.size();
        Solve();
    }
}

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

typedef vector<long long> BigNum;
const long long base = 1e6;

void fix(BigNum &a) {
    a.push_back(0);
    int sz = a.size() - 1;
    REP(i, sz) {
        a[i + 1] += a[i] / base;
        a[i] %= base;
        if (a[i] < 0) {
            a[i] += base;a[i + 1]--;
        }
    }
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}
BigNum operator+(BigNum a, BigNum b) {
    BigNum c; c.clear();
    if (a.size() < b.size()) swap(a, b);
    c.resize(a.size());
    REP(i, b.size()) c[i] = a[i] + b[i];
    FOR(i, b.size(), (int)a.size() - 1) c[i] = a[i];
    fix(c);
    return c;
}
BigNum operator-(BigNum a, BigNum b) {
    BigNum c; c.clear();
    c.resize(a.size());
    REP(i, b.size()) c[i] = a[i] - b[i];
    FOR(i, b.size(), (int)a.size() - 1) c[i] = a[i];
    fix(c);
    return c;
}

BigNum operator/(BigNum a, long long b) {
    int sz = a.size() - 1;
    long long rem = 0;
    BigNum c; c.clear();
    c.resize(a.size());
    FORD(i, sz, 0) {
        rem *= base;
        c[i] = (rem + a[i]) / b;
        rem = (rem + a[i]) % b;
    }
    fix(c);
    return c;
}

BigNum To(int x) {
    BigNum c;c.clear();
    c.push_back(x);
    return c;
}

bool operator<= (BigNum a, BigNum b) {
    if (a.size() < b.size()) return true;
    if (a.size() > b.size()) return false;
    FORD(i, a.size() - 1, 0) {
        if (a[i] > b[i]) return false;
        if (a[i] < b[i]) return true;
    }
    return true;
}

BigNum operator* (BigNum a, BigNum b) {
    BigNum c; c.clear(); c.resize(a.size() + b.size());
    REP(i, a.size()) REP(j, b.size()) c[i + j] += a[i] * b[j];
    fix(c);
   // Arr(c, 0, (int)c.size() - 1);
    return c;
}

istream& operator >> (istream& cin, BigNum &a) {
    string st; cin >> st;
    a.clear(); a.resize(st.size() / 6 + 1);
    REP(i, st.size()) {
        int id = (st.size() - i - 1) / 6;
        a[id] = a[id] * 10 + (st[i] - '0');
    }
    fix(a);
    return cin;
}

ostream& operator << (ostream& cout, BigNum &a) {
    printf("%d", a.back());
    FORD(i, (int)a.size() - 2, 0) printf("%06d", a[i]);
    return cout;
}

int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    double stime = clock();
    #else
    freopen("NUMBER.inp","r",stdin);
    freopen("NUMBER.out","w",stdout);
    #endif //NERO
    IO;
    BigNum a, b;
    cin >> a >> b;
    BigNum One = To(1);
    BigNum l = One, r = b, high = One, low = One;
    while (l + To(2) <= r) {
        BigNum m = (l + r) / 2;
    //    Arr(m, 0, (int)m.size() - 1);
        if (m * (m + One) <= b) {
            high = m;
            l = m;
        } else r = m;
    }
    l = One, r = a;
    while (l + To(2) <= r) {
        BigNum m = (l + r) / 2;
        if (a <= m * (m + One)) {
            low = m;
            r = m;
        } else l = m;
    }
    BigNum ans = high - low + One;
    cout << ans;
    #ifdef NERO
    double etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.";
    #endif // NERO
}

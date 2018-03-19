#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a) for (int i = 0; i < (a); ++i)
#define DEBUG(x) { cerr << #x << '=' << x << endl; }
#define Arr(a, l, r) { cerr << #a << " = {"; FOR(_, l, r) cerr << ' ' << a[_]; cerr << "}\n"; }
#define N 31
#define pp pair<int, int>
#define endl '\n'
#define IO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define taskname "SEED"
#define bit(S, i) (((S) >> (i)) & 1)
using namespace std;
const int SN = 1 << 15;
int n, m, star;
string seed;
long long dp[N << 1][N][SN], POW[N];
int used[N << 1][N][SN], nxt[N][SN][2], s[N][SN][2];

string Create(int k, int status, int now) {
    int z = status;
    string res;
    REP(i, k) {
        if (seed[i] == '1') res.push_back('1');
        else {
            res.push_back('0' + z % 2);
            z /= 2;
        }
    }
    res.push_back('0' + now);
    return res;
}

long long g[N];

void Init() {
    m = seed.size();
    star = 0;
    int xx = 1;
    REP(i, m) if (seed[i] == '*') { star++; g[i] = xx; xx *= 2; }
    POW[0] = 1;
    FOR(i, 1, n) POW[i] = POW[i - 1] * 2;
    nxt[0][0][0] = 0; s[0][0][0] = 0;
    nxt[0][0][1] = 1; s[0][0][0] = 0;
    FOR(k, 1, m - 1) FOR(status, 0, (1 << star) - 1) {
        if (seed[k] == '*') {
            // Case choose 0
            nxt[k][status][0] = k + 1;
            s[k][status][0] = status;
            // Case choose 1
            nxt[k][status][1] = k + 1;
            s[k][status][1] = status + g[k];
        }
        else {
            nxt[k][status][1] = k + 1;
            s[k][status][1] = status;
            nxt[k][status][0] = 0;
            s[k][status][0] = 0;
            string now = Create(k, status, 0);
            FORD(j, k, 1) {
                bool ok = true;
                string newS = now.substr(k + 1 - j, j);
                int newStatus = 0;
                REP(z, j) {
                    if (seed[z] == '1' && newS[z] != '1') {
                        ok = false;break;
                    } else {
                        if (seed[z] == '*' && newS[z] == '1') {
                            newStatus += g[z];
                        }
                    }
                }
                if (ok) {
                    nxt[k][status][0] = j;
                    s[k][status][0] = newStatus;
                    break;
                }
            }
        }
    }
}
long long Cal(int id, int matched, int status) {
    if (matched == m) {
        return POW[n - id];
    }
    if (id == n)
        return 0;
    if (used[id][matched][status]) return dp[id][matched][status];
    used[id][matched][status] = true;
    long long &res = dp[id][matched][status];
    res = Cal(id + 1, nxt[matched][status][0], s[matched][status][0]);
    res += Cal(id + 1, nxt[matched][status][1], s[matched][status][1]);
    return res;
}
void Buffalo() {
    int cnt = 0;
    REP(mask, 1 << n) {
        REP(start, n) {
            int matched = 0;
            FOR(j, start, n - 1) {
                if (seed[matched] == '1' && bit(mask, j) == 0) break;
                matched++;
                if (matched == seed.size()) break;
            }
            if (matched == seed.size()) {
                cnt++; break;
            }
        }
    }
    cout << cnt;
}
int main() {

        freopen(taskname".inp","r",stdin);
        freopen(taskname".out","w",stdout);
    IO;
    cin >> n >> seed;
    if (n < seed.size()) {
        cout << 0; return 0;
    }
    if (n <= 20) {
        Buffalo();
        return 0;
    }
    Init();
    cout << Cal(0, 0, 0);
}

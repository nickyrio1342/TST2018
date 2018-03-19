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

int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.ans","w",stdout);
    double stime = clock();
    #else
        //freopen("taskname.inp","r",stdin);
        //freopen("taskname.out","w",stdout);
    #endif //NERO
    IO;
    cin >> n >> seed;
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
    #ifdef NERO
    double etime = clock();
    cerr << "Execution time: " << (etime - stime) / CLOCKS_PER_SEC * 1000 << " ms.\n";
    #endif // NERO
}

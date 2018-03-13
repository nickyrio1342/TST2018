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

#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;
const long long base = 29;

long long Hash[N], Rev_Hash[N], POW[N];
string st;
int n;

void InitHash() {
    POW[0] = 1;
    FOR(i, 1, n) POW[i] = POW[i - 1] * base % MOD;
    Hash[0] = 1;
    Rev_Hash[0] = 1;
    string rev_st = st;
    reverse(rev_st.begin(), rev_st.end());
    st = '~' + st;
    rev_st = '~' + rev_st;
    FOR(i, 1, n) {
        Hash[i] = (Hash[i - 1] + st[i] - 'a') * base % MOD;
        Rev_Hash[i] = (Rev_Hash[i - 1] + rev_st[i] - 'a') * base % MOD;
    }
}

long long GetHash(int i, int j){
    return (Hash[j] - Hash[i - 1] * POW[j - i + 1] + MOD * MOD) % MOD;
}
long long GetRevHash(int i, int j) {
    int ii = n - i + 1, jj = n - j + 1;
    return (Rev_Hash[ii] - Rev_Hash[jj - 1] * POW[ii - jj + 1] + MOD * MOD) % MOD;
}
long long cntPalin[N];
int even[N], odd[N];
long long totalPalin;
vector<int> eOdd[N], eEven[N];

void InitPalin() {
    totalPalin = 0;
    //Case odd
    FOR(i, 1, n) {
        int l = 1, r = min(i - 1, n - i), cur = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (GetHash(i, i + mid) == GetRevHash(i - mid, i)) {
                cur = mid;
                l = mid + 1;
            } else r = mid - 1;
        }
        odd[i] = cur;
        eOdd[i - cur - 1].push_back(i);
        eOdd[i + cur + 1].push_back(i);
        totalPalin += cur + 1;
        cntPalin[i - cur]++;cntPalin[i + 1]--;
        cntPalin[i + 1]--;cntPalin[i + cur + 2]++;
    }
    //Case even
    even[n] = -1;
    FOR(i, 1, n - 1) if (st[i] == st[i + 1]) {
        int l = 1, r = min(i - 1, n - i - 1), cur = 0;;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (GetHash(i + 1, i + mid + 1) == GetRevHash(i - mid, i)) {
                cur = mid;
                l = mid + 1;
            } else r = mid - 1;
        }
        even[i] = cur;
        eEven[i - cur - 1].push_back(i);
        eEven[i + cur + 2].push_back(i);
        totalPalin += cur + 1;
        cntPalin[i - cur]++; cntPalin[i + 1]--;
        cntPalin[i + 2]--; cntPalin[i + cur + 3]++;
    } else {
        even[i] = -1;
        eEven[i].push_back(i);
        eEven[i + 1].push_back(i);
    }
    FOR(i, 1, n) cntPalin[i] += cntPalin[i - 1];
    FOR(i, 1, n) cntPalin[i] += cntPalin[i - 1];
 //   Arr(cntPalin, 1, n);
 //   DEBUG(totalPalin);
}

long long Palin[26];
void Solve() {
    long long ans = totalPalin;
    FOR(i, 1, n) { // Case delete i
        long long newPalin = totalPalin - cntPalin[i] + odd[i] + 1;
        REP(j, 26) Palin[j] = 0;
        // Case odd
        for (int id : eOdd[i]) {
            int l, r, c;
            if (id > i) {
                l = i - 1, r = id + odd[id] + 2;
                if (r == n + 2) continue;
                c = st[r - 1] - 'a';
            }
            else {
                l = id - odd[id] - 2, r = i + 1;
                if (l == -1) continue;
                c = st[l + 1] - 'a';
            }
            int le = 0, ri = min(n - r, l - 1), cur = -1;
            while (le <= ri) {
                int mid = (le + ri) >> 1;
                if (GetHash(r, r + mid) == GetRevHash(l - mid, l)) {
                    cur = mid;
                    le = mid + 1;
                } else ri = mid - 1;
            }
            Palin[c] += cur + 2;
        }
        // Case even
        for (int id : eEven[i]) {
            int l, r, c;
            if (id >= i) {
                l = i - 1, r = id + even[id] + 3;
                if (r == n + 2) continue;
                c = st[r - 1] - 'a';
            }
            else {
                l = id - even[id] - 2, r = i + 1;
                if (l == -1) continue;
                c = st[l + 1] - 'a';
            }
            int le = 0, ri = min(n - r, l - 1), cur = -1;
            while (le <= ri) {
                int mid = (le + ri) >> 1;
                if (GetHash(r, r + mid) == GetRevHash(l - mid, l)) {
                    cur = mid;
                    le = mid + 1;
                } else ri = mid - 1;
            }
            Palin[c] += cur + 2;
        }
        REP(j, 26) ans = max(ans, newPalin + Palin[j]);
    }
    cout << ans;
}
int main() {
    #ifdef NERO
    freopen("test.inp","r",stdin);
    freopen("test.out","w",stdout);
    #endif //NERO
    IO;
    cin >> st;
    n = st.size();
    InitHash();
    InitPalin();
    Solve();
}

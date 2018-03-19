#include "horse1lib.h"
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
int n, k, a[N];
#ifdef NERO
#define RM (RAND_MAX + 1)
#define ra (long long) rand()

long long Rand(long long l, long long r) {
    return l + (ra * RM * RM * RM + ra * RM * RM + ra * RM + ra) % (r - l + 1);
}
int aa[1111], ab[1111], ac[1111];

int get_n() {
    srand(time(NULL));
	int n; std::cin >> n;
    FOR(i, 1, n) aa[i] = Rand(aa[i - 1] + 1, aa[i - 1] + 10);
    FOR(i, 1, n) ab[i] = Rand(1, 10), ac[i] = i;
    sort(ac + 1, ac + n + 1, [] (int x, int y) {
         return ab[x] > ab[y];
         });
    FOR(i, 1, n) ab[i] = aa[ac[i]];
    FOR(i, 1, n) aa[i] = ab[i];
    sort(aa + 1, aa + n + 1, greater<int>());
    Arr(ab, 1, n);
    return n;
	//return 2;
}

int get_k() {
    int k; std::cin >> k;
    return k;
}

int compare(int i, int j) {
	return ab[i] > ab[j];
}

void guess(int res) {
    DEBUG(res);
    if (aa[k] == ab[res]) printf("correct!"); //correct
    else printf("Incorrect!!");
  //  getchar();
}


#endif // NERO
int IT[4444];
int Compare(int i, int j) {
    if (i == -1) return j;
    if (j == -1) return i;
    return compare(i, j) ? i : j;
}
void Build(int k, int l, int r) {
    if (l == r) {
        IT[k] = l; return;
    }
    int m = (l + r) >> 1;
    Build(k << 1, l, m);
    Build(k << 1 | 1, m + 1, r);
    IT[k] = Compare(IT[k << 1], IT[k << 1 | 1]);
}

void Disable(int k, int l, int r, int u) {
    if (l == r) { IT[k] = -1; return; }
    int m = (l + r) >> 1;
    if (u <= m) Disable(k << 1, l, m, u);
    else Disable(k << 1 | 1, m + 1, r, u);
    IT[k] = Compare(IT[k << 1], IT[k << 1 | 1]);
}

int main() {
    IO;
    n = get_n();
    k = get_k();
    Build(1, 1, n);
    if (k == 1) guess(IT[1]);
    else {
        Disable(1, 1, n, IT[1]);
        if (k == 2) guess(IT[1]);
        else {
            Disable(1, 1, n, IT[1]);
            guess(IT[1]);
        }
    }
}

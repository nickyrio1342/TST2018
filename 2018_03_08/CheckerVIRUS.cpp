#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<= b; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define DEBUG(x) { cerr << #x << " = " << x << endl; }
#define Arr(A, l, r) { cerr << #A  << " = "; FOR(_, l, r) cerr << A[_] << ' '; cerr << endl; }
#define N 555
#define pp pair<long long, int>
#define next __next
#define prev __prev
#define __builtin_popcount __builtin_popcountll
#define bit(S, i) (((S) >> i) & 1)
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define ra (long long) rand()
#define rm (RAND_MAX + 1)

using namespace std;

long long Rand(long long l, long long r) {
    return l + (ra * rm * rm * rm + ra * rm * rm + ra * rm + ra) % (r - l + 1);
}

int c[N][N];
void Generate() {
    ofstream f("TEST.inp");
    int test = 1;
    REP(i, test) {
        int n = Rand(5, 5), m = Rand(1, 1);
        f << n << ' ';
        REP(j, m) f << Rand(0, 0); f << endl;
    } 
}

int main() {
    srand(time(NULL));
    Generate(); return 0;
    REP(i, 1) {
        double stime = clock();
        cerr << "Generating..." << endl;
        Generate();
        int Time = (clock() - stime) / CLOCKS_PER_SEC * 1000;
        cerr << "Generate successfully - " << Time << " ms\n"; 
        //system("VIRUS3");
        stime = clock();
        system("VIRUS");
        Time = (clock() - stime) / CLOCKS_PER_SEC * 1000;
        cerr << "Test " << i << " - Time used: " << Time << endl;
        continue;
        if (system("fc test.out test.ans")) {
            cerr << "Wrong!!";
            getchar(); return 0;
        }
        cerr << "Correct!\n";
    }
    cerr << "All tests are correct:))\n"; getchar();
}

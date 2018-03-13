#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<= b; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define DEBUG(x) { cerr << #x << " = " << x << endl; }
#define Arr(A, l, r) { cerr << #A  << " = "; FOR(_, l, r) cerr << A[_] << ' '; cerr << endl; }
#define N 5550
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

int pos[N];
void Generate() {
    ofstream f("TEST.inp");
    int n = Rand(1000, 2000);
    pos[0] = Rand(1e8, 5e8);
    f << n << ' ' << pos[0] << endl;
    FOR(i, 1, n) {
        //pos[i] = Rand(pos[i - 1] + 1, pos[i - 1] + 1e3);
        pos[i] = 1e9 - i + 1;
        if (i > n / 2) pos[i] = i - 1;
        f << pos[i] << ' ' << Rand(1e3, 1e6) << ' ' << Rand(1e3, 1e6) << endl;
    }
}

int main() {
    srand(time(NULL));
    //Generate(); return 0;
    REP(i, 10000) {
        double stime = clock();
        cerr << "Generating..." << endl;
        Generate();
        int Time = (clock() - stime) / CLOCKS_PER_SEC * 1000;
        cerr << "Generate successfully - " << Time << " ms\n"; 
        system("12822_Quan");
        stime = clock();
        system("12822");
        Time = (clock() - stime) / CLOCKS_PER_SEC * 1000;
        cerr << "Test " << i << " - Time used: " << Time << endl;
       // continue;
        if (system("fc test.out test.ans")) {
            cerr << "Wrong!!";
            getchar(); return 0;
        }
        cerr << "Correct!\n";
    }
    cerr << "All tests are correct:))\n"; getchar();
}

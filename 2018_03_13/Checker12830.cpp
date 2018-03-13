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
    int n = Rand(5, 10), k = Rand(1, 4);
    f << n << ' ' << k << endl;
    FOR(i, 2, n) {
        f << Rand(1, i - 1) << ' ' << i << ' ' << Rand(1, 10) << endl;
    } 
}
#define esp 1e-6
int main() {
    srand(time(NULL));
 //   Generate(); return 0;
    int TimeLimit = 4000;
    REP(i, 200) {
        double stime = clock();
        cerr << "Generating..." << endl;
        Generate();
        int Time = (clock() - stime) / CLOCKS_PER_SEC * 1000;
        cerr << "Generate successfully - " << Time << " ms\n"; 
        system("12830_buff");
        stime = clock();
        system("12830");
        Time = (clock() - stime) / CLOCKS_PER_SEC * 1000;
        cerr << "Test " << i << " - Time used: " << Time << endl;
        if (Time > TimeLimit) {
            cerr << "Time limit exceeded\n";
            getchar();
            return 0;
        }
        ifstream f("TEST.out");
        double ans1, ans2;
        f >> ans1;
        ifstream g("TEST.ans");
        g >> ans2;
        cerr << "Answer: "<<ans2 << "\nOutput: " << ans1 << endl;
        if (abs(ans1 - ans2) > esp) {
            cerr << "Wrong answer\n";
            getchar(); return 0;
        }
        /*
        if (system("fc test.out test.ans")) {
            cerr << "Wrong!!";
            getchar(); return 0;
        }*/
        cerr << "Correct!\n";
    }
    cerr << "All tests are correct:))\n"; getchar();
}

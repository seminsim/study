#include <cmath>
#include <cstdio>
#include <list>
#include <set>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int BIG = 1234567;

int gcd(int a, int b)
{
  while (true) {
    if (a == b) return a;
    if (a > b) {
      a -= (a/b) * b;
      if (a == 0) return b;
    } else {
      b -= (b/a) * a;
      if (b == 0) return a;
    }
  }
}

inline int isLess(int n, int d, int n2, int d2)
{
  return (n * d2) < (n2 * d);
}

int N;
int minAvrN = BIG, minAvrD = 1;

// [from][to] = distance(weight);
vector< vector<int> > w;
// [distance][to] = weight with the distance;
vector< vector<int> > dw;

void input()
{
  cin >> N;

  // initialize, and setup w
  w.resize(N, vector<int>(N,BIG));
  for (int f=0; f<N; ++f) {
    for (int t=0; t<N; ++t) {
      int w_i;
      cin >> w_i;
      if (f == t) continue; // TODO: remove this
      if (w_i > 0) {
        w[f][t] = w_i;
      }
    }
  }

  // initialize dw
  dw.resize(N+1, vector<int>(N,BIG));
  dw[0][0] = 0;
}

void tableBuild()
{
  for (int d=1; d<=N; ++d) {
    for (int k=0; k<N; ++k) {
      if (dw[d-1][k] >= BIG) continue;
      for (int t=0; t<N; ++t) {
        if (w[k][t] >= BIG) continue;
        int curD = dw[d-1][k] + w[k][t];
        dw[d][t] = min(dw[d][t], curD);
      }
    }
  }
}

tuple<int,int> solve()
{
  tableBuild();

  for (int i=0; i<N; ++i) { // node
    if (dw[N][i] >= BIG) continue;

    int maxNodeAvrN = 0;
    int maxNodeAvrD = 1;
    for (int ds=0; ds<N-1; ++ds){ // starting node
      if (dw[ds][i] >= BIG) continue;
      int n = dw[N][i] - dw[ds][i];
      if (n < 0) continue;
      if (isLess(maxNodeAvrN, maxNodeAvrD, n, N-ds)){
        maxNodeAvrN = n;
        maxNodeAvrD = N-ds;
      }
    }
    if (maxNodeAvrN == 0) continue;
    if (isLess(maxNodeAvrN, maxNodeAvrD, minAvrN, minAvrD)) {
      minAvrN = maxNodeAvrN;
      minAvrD = maxNodeAvrD;
    }
  }

  int gcdVal = gcd(minAvrN, minAvrD);
  return make_tuple(minAvrN/gcdVal, minAvrD/gcdVal);
}

int main() {
  input();

  int p, q;
  tie(p, q) = solve();

  cout << p << "/" << q << endl;

  return 0;
}

#include <cmath>
#include <cstdio>
#include <list>
#include <set>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int BIG = 123456789;

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
int minCost = BIG;
int maxBuildD;
int minAvrN = BIG, minAvrD = 1;

// dist [1,2,4,6,8,10,...]
// [dist][fom][to] = w;
vector< vector< vector<int> > > d;
void input()
{
  int w;
  cin >> N;
  maxBuildD = 1 + (N)/2;
  d.resize(maxBuildD, vector< vector<int> >(N, vector<int>(N,BIG)));

  for (int f=0; f<N; ++f) {
    for (int t=0; t<N; ++t) {
      cin >> w;
      if (f == t) continue; // TODO: remove this
      if (w > 0) d[0][f][t] = w;
      if (w > 0 && w < minCost) minCost = w;
    }
  }
}

tuple<int,int> solve()
{
  for (int l=2; l<=N; l+=2) {
    //--------------------------------
    // D2, D4, D6, .... D(even)
    //--------------------------------

    // min additional cost
    int minAddtionalCost = ((N-l) * minCost);

    // d1, dPrev => d
    int currentMinCost = BIG;
    int f, k, dfk;
    bool updated = false;
    for (int f=0; f<N; ++f) {
      for (int k=0; k<N; ++k) {
        if (f==k) continue;
        dfk = (l==2) ? d[0][f][k] : d[1][f][k];
        int tub = ((l==N) ? f+1 : N);
        if (dfk >= BIG) continue;
        for (int t=(l==N) ? f : 0; t<tub; ++t) {
          if (k==t) continue;
          int dkt = (l==2) ? d[0][k][t] : d[(l/2)-1][k][t];
          if (dkt >= BIG) continue;
          if (f==t){
            // update min
            if (dfk + dkt < currentMinCost) currentMinCost = dfk + dkt;
          } else if (l==2 || isLess(dfk + dkt + minAddtionalCost, N, minAvrN, minAvrD)){
            // update d
            d[l/2][f][t] = min(d[l/2][f][t], dfk + dkt);
            updated = true;
          }
        }
      }
    }
    if (isLess(currentMinCost, l, minAvrN, minAvrD)) {
      minAvrN = currentMinCost;
      minAvrD = l;
    }
    if (!updated) break;
    //--------------------------------
    // D3, D5, D7, .... D(odd)
    //--------------------------------
    if (l==N) break;

    int x = 0;
    int y = (l/2);
    // d1, dPrev => d
    for (int f=0; f<N; ++f) {
      for (int k=0; k<N; ++k) {
        if (f==k) continue;
        int dfk = d[x][f][k];
        int dkt = d[y][k][f];
        if (dfk >= BIG) continue;
        if (dkt >= BIG) continue;
        if (dfk + dkt < currentMinCost) currentMinCost = dfk + dkt;
      }
    }
    // update min
    if (isLess(currentMinCost, l, minAvrN, minAvrD)) {
      minAvrN = currentMinCost;
      minAvrD = l;
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

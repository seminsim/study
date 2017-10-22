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

// [from][to] = distance
// [l][f][t] = w;
vector< vector< vector<int> > > d;
void input()
{
  int w;
  cin >> N;
  maxBuildD = 1 + (N-1)/2;
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

void tableBuild()
{
  // [optimize] fk list for optimization
  list< tuple<int, int, int> > fkList;
  for (int f=0; f<N; ++f) {
    for (int k=0; k<N; ++k) {
      if (d[0][f][k] < BIG) fkList.push_back(make_tuple(f,k,d[0][f][k]));
    }
  }
  auto fkBegin = fkList.begin();
  auto fkEnd = fkList.end();

  for (int l=2; l<=maxBuildD; ++l) {
    // min additional cost
    int minAddtionalCost = ((N-l) * minCost);

    // d1, dPrev => d
    int minCost = BIG;
    int f, k, d1fk;
    for (auto fkIt = fkBegin; fkIt != fkEnd; ++ fkIt) {
      tie(f, k, d1fk) = *fkIt;
      int tub = ((l==N) ? f+1 : N);
      for (int t=(l==N) ? f : 0; t<tub; ++t) {
        if (k==t) continue;
        int dprevkt = d[l-2][k][t];
        if (dprevkt >= BIG) continue;
        if (f==t){
          // update min
          if (d1fk + dprevkt < minCost) minCost = d1fk + dprevkt;
        } else if (l==2 || isLess(d1fk + dprevkt + minAddtionalCost, N, minAvrN, minAvrD)){
          // update d
          d[l-1][f][t] = min(d[l-1][f][t], d1fk + dprevkt);
        }
      }
    }
    if (isLess(minCost, l, minAvrN, minAvrD)) {
      minAvrN = minCost;
      minAvrD = l;
    }
  }
}

tuple<int,int> solve()
{
  tableBuild();
  // bigger half

  for (int l=maxBuildD+1; l<=N; ++l){
    int x = (l/2) -1;
    int y = (l-x) -2;
    // d1, dPrev => d
    int minCost = BIG;
    for (int f=0; f<N; ++f) {
      for (int k=0; k<N; ++k) {
        int dfk = d[x][f][k];
        int dkt = d[y][k][f];
        if (dfk >= BIG) continue;
        if (dkt >= BIG) continue;
        if (dfk + dkt < minCost) minCost = dfk + dkt;
      }
    }
    // update min
    if (isLess(minCost, l, minAvrN, minAvrD)) {
      minAvrN = minCost;
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

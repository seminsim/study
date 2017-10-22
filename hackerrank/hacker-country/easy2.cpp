#include <cmath>
#include <cstdio>
#include <list>
#include <set>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define DEBUG 0
#define ONDEBUG if(DEBUG)

const int BIG = 123456789;
const double BIG_DOUBLE = 123456789.0;

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
// [from][to] = distance
vector< vector<int> > d1;
vector< vector<int> > dPrev;
vector< vector<int> > d;
void input()
{
  int w;
  cin >> N;
  d1.resize(N);
  dPrev.resize(N);
  d.resize(N);
  for (int f=0; f<N; ++f) {
    d1[f].resize(N, BIG);
    dPrev[f].resize(N, BIG);
    d[f].resize(N, BIG);
    for (int t=0; t<N; ++t) {
      cin >> w;
      if (f == t) continue; // TODO: remove this
      if (w > 0) dPrev[f][t] = d1[f][t] = w;
      if (w > 0 && w < minCost) minCost = w;
    }
  }
}

void print()
{
  cout << "d1" << endl;
  for (int f=0; f<N; ++f){
    for (int t=0; t<N; ++t){
      cout << " " << d1[f][t];
    }
    cout << endl;
  }
  cout << endl;

  cout << "dPrev" << endl;
  for (int f=0; f<N; ++f){
    for (int t=0; t<N; ++t){
      cout << " " << dPrev[f][t];
    }
    cout << endl;
  }
  cout << endl;

  cout << "d" << endl;
  for (int f=0; f<N; ++f){
    for (int t=0; t<N; ++t){
      cout << " " << d[f][t];
    }
    cout << endl;
  }
  cout << endl;
}

tuple<int,int> solve()
{
  // [optimize] fk list for optimization
  list< tuple<int, int, int> > fkList;
  for (int f=0; f<N; ++f) {
    for (int k=0; k<N; ++k) {
      if (d1[f][k] < BIG) fkList.push_back(make_tuple(f,k, d1[f][k]));
    }
  }
  auto fkBegin = fkList.begin();
  auto fkEnd = fkList.end();

  ONDEBUG print();
  int minAvrN = BIG, minAvrD = 1;
  for (int l=2; l<=N; ++l) {
    // init d
    for (int f=0; f<N; ++f) {
      fill(d[f].begin(), d[f].end(), BIG);
    }

    // min additional cost
    int minAddtionalCost = ((N-l) * minCost);

    // d1, dPrev => d
    int f, k, d1fk;
    for (auto fkIt = fkBegin; fkIt != fkEnd; ++ fkIt) {
      tie(f, k, d1fk) = *fkIt;
      int tub = ((l==N) ? f+1 : N);
      for (int t=(l==N) ? f : 0; t<tub; ++t) {
        if (k==t) continue;
        ONDEBUG cout << f << "->" << k << "->" << t << " " << d1[f][k] << " " << dPrev[k][t] << endl;
        int dprevkt = dPrev[k][t];
        if (dprevkt >= BIG) continue;
        if (f==t){
          // update min
          if (isLess(d1fk + dprevkt, l, minAvrN, minAvrD)) {
            minAvrN = d1fk + dprevkt;
            minAvrD = l;
          }
        } else if (l==2 || isLess(d1fk + dprevkt + minAddtionalCost, N, minAvrN, minAvrD)){
          // update d
          d[f][t] = min(d[f][t], d1fk + dprevkt);
        }
      }
    }
     ONDEBUG print();

    // dPrev = d
    swap(dPrev, d);
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

#include <cmath>
#include <cstdio>
#include <map>
#include <tuple>
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

inline int nodeid(int f, int t, int N) { return f*N + t; }
inline tuple<int,int> extract(int nid, int N) { return make_tuple(nid/N, nid%N); }

int N;
// d1[node] = w
map<int,int> d1;
map<int, map<int,int> > dPrev;
map<int, map<int,int> > d;
void input()
{
  int w;
  cin >> N;
  for (int f=0; f<N; ++f) {
    for (int t=0; t<N; ++t) {
      cin >> w;
      if (f == t) continue; // TODO: remove this
      if (w > 0) {
        d1[nodeid(f,t,N)] = w;
        dPrev[f][t] = w;
      }
    }
  }
}

tuple<int,int> solve()
{
  auto fkBegin = d1.begin();
  auto fkEnd = d1.end();

  int minAvrN = BIG, minAvrD = 1;
  for (int l=2; l<=N; ++l) {
    // init d
    d.clear();

    // d1, dPrev => d
    int f, k, d1fk;
    for (auto fkIt=fkBegin; fkIt!=fkEnd; ++fkIt) {
      tie(f, k) = extract(fkIt->first, N);
      d1fk = fkIt->second;

      auto ktEnd = dPrev[k].end();
      for (auto ktIt=dPrev[k].begin(); ktIt!=ktEnd; ++ktIt) {
        int t, dprevkt;
        tie(t, dprevkt) = *ktIt;

        if (f==t) {
          // update min
          if (isLess(d1fk + dprevkt, l, minAvrN, minAvrD)) {
            minAvrN = d1fk + dprevkt;
            minAvrD = l;
          }
        } else if (l==2 || isLess(d1fk + dprevkt, N, minAvrN, minAvrD)) {
          // update d
          if (d[f].find(t) == d[f].end())
            d[f][t] = d1fk + dprevkt;
          else
            d[f][t] = min(d[f][t], d1fk + dprevkt);
        }
      }
    }
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

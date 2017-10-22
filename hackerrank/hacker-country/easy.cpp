#include <cmath>
#include <cstdio>
#include <set>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define DEBUG 1
#define ONDEBUG if(DEBUG)

const double BIG_DOUBLE = 123456789.0;

int gcd(int a, int b)
{
  int t;
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

int N;
// [from] = <to, weight>
vector< set< tuple<int,int> > > e;
void input()
{
  int w;
  cin >> N;
  e.clear();
  e.resize(N);
  for (int i=0; i<N; ++i) {
    for (int j=0; j<N; ++j) {
      cin >> w;
      if (w > 0) e[i].insert(make_tuple(j, w));
    }
  }
}

// sumWeight, totalEdges
tuple<int,int> findMinAvrWeight(int start, int current, vector<int>& ban, int sumWeight, int totalEdges)
{
  //ONDEBUG cout << "findMinAvrWeight " << start << " " << current << " " << sumWeight << " " << totalEdges << endl;
  double minAvr = BIG_DOUBLE;
  double newAvr;

  int minSumWeight = 0;
  int minTotalEdges = 0;

  auto begin = e[current].begin();
  auto end = e[current].end();

  int to, w;
  for (auto it = begin; it != end; ++it) {
    tie(to, w) = *it;
    if (to == start) {
      // return to starting point
      ONDEBUG cout << "LOOP " << start << " " << current << " " << sumWeight << " " << totalEdges << endl;
      newAvr = (totalEdges + 1 < 2) ? BIG_DOUBLE : (double)(sumWeight + w) / (double)(totalEdges + 1);
      if (newAvr < minAvr) {
        minAvr = newAvr;
        minSumWeight = sumWeight + w;
        minTotalEdges = totalEdges + 1;
      }
    } else if (ban[to]) {
      continue;
    } else {
      // search
      ban[to] = true;
      int nestedMinSumWeight, nestedMinTotalEdges;
      tie(nestedMinSumWeight, nestedMinTotalEdges) = findMinAvrWeight(start, to, ban, sumWeight + w, totalEdges + 1);
      ban[to] = false;

      newAvr = (nestedMinTotalEdges + 1 < 2) ? BIG_DOUBLE : (double)nestedMinSumWeight / (double)nestedMinTotalEdges;
      if (newAvr < minAvr) {
        minAvr = newAvr;
        minSumWeight = nestedMinSumWeight;
        minTotalEdges = nestedMinTotalEdges;
      }
    }
  }

  //ONDEBUG cout << "findMinAvrWeight " << start << " " << current << " " << sumWeight << " " << totalEdges << " RET=" << minSumWeight << " " << minTotalEdges << endl;
  return make_tuple(minSumWeight, minTotalEdges);
}

tuple<int,int> solve()
{
  int sumWeight, totalEdges;
  int minSumWeight, minTotalEdges;
  double avr, minAvr = BIG_DOUBLE;

  vector<int> ban(N, false);
  for (int i=0; i<N-1; ++i) {
    tie(sumWeight, totalEdges) = findMinAvrWeight(i, i, ban, 0, 0);
    avr = totalEdges < 2 ? BIG_DOUBLE : (double)sumWeight / (double)totalEdges;
    if (avr < minAvr) {
      minAvr = avr;
      minSumWeight = sumWeight;
      minTotalEdges = totalEdges;
    }
    ban[i] = true;;
  }

  int gcdval = gcd(minSumWeight, minTotalEdges);
  return make_tuple(minSumWeight/gcdval, minTotalEdges/gcdval);
}

int main() {
  input();

  int p, q;
  tie(p, q) = solve();

  cout << p << "/" << q << endl;

  return 0;
}

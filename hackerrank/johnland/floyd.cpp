#include <cmath>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

int N, M;
vector< vector< set<int> > > d;

void input()
{
  cin >> N >> M;
  d.resize(N, vector< set<int> >(N));
  int f, t, w;
  for (int i=0; i<M; ++i) {
    cin >> f >> t >> w;
    if (f<t)
      d[f-1][t-1].insert(w);
    else
      d[t-1][f-1].insert(w);
  }
}

void solve()
{
  int dfk, dkt, dft;
  for (int k=0; k<N; ++k) {
    for (int f=0; f<N; ++f) {
      if (k==f) continue;
      int af, ak;
      if (f<k) { af=f; ak=k; } else { af=k; ak=f; }
      if (d[af][ak].empty()) continue;

      for (int t=f+1; t<N; ++t) {
        if (k==t) continue;
        int bk, bt;
        if (k<t) { bk=k; bt=t; } else { bk=t; bt=k; }

        if (d[bk][bt].empty()) continue;

        dfk = *(d[af][ak].rbegin());
        dkt = *(d[bk][bt].rbegin());
        if (d[f][t].empty()) {
          d[f][t] = d[af][ak];
          d[f][t].insert(d[bk][bt].begin(), d[bk][bt].end());
        }else {
          dft = *(d[f][t].rbegin());
          if (dfk < dft && dkt < dft){
            d[f][t] = d[af][ak];
            d[f][t].insert(d[bk][bt].begin(), d[bk][bt].end());
          }
        }
      }
    }
  }

  map<int, int> sumDigits;
  for (int f=0; f<N; ++f) {
    for (int t=f+1; t<N; ++t) {
      auto& s = d[f][t];
      auto itEnd = s.end();
      for (auto it=s.begin(); it!=itEnd; ++it) {
        int d = *it;
        while (true) {
          if (sumDigits.find(d) == sumDigits.end() || sumDigits[d] == 0) {
            sumDigits[d] = 1;
            break;
          }
          sumDigits[d] = 0;
          d++;
        }
      }
    }
  }

  int maxDigit = sumDigits.rbegin()->first;
  for (int i=maxDigit; i>=0; --i) {
    if (sumDigits[i] == 1)
      cout << 1;
    else
      cout << 0;
  }
}

int main() {
  input();
  solve();
  return 0;
}

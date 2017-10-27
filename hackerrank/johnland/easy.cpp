#include <cmath>
#include <cstdio>
#include <bitset>
#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

const int BIG = numeric_limits<int>::max();

int N, M;
vector< vector<int> > d;

void input()
{
  cin >> N >> M;
  d.resize(N, vector<int>(N, BIG));
  int f, t, w;
  for (int i=0; i<M; ++i) {
    cin >> f >> t >> w;
    d[f-1][t-1] = 1<<w;
    d[t-1][f-1] = 1<<w;
  }
}

int solve()
{
  int dfk, dkt;
  for (int k=0; k<N; ++k) {
    for (int f=0; f<N; ++f) {
      if (k==f) continue;
      if (f<k && d[f][k] == BIG) continue;
      if (k<f && d[k][f] == BIG) continue;
      for (int t=f+1; t<N; ++t) {
        if (k==t) continue;
        if (f<k) dfk = d[f][k]; else dfk = d[k][f];
        if (k<t) dkt = d[k][t]; else dkt = d[t][k];
        if (dkt == BIG) continue;
        if (dfk + dkt < d[f][t]) {
          d[f][t] = dfk + dkt;
        }
      }
    }
  }

  int sum = 0;
  for (int f=0; f<N; ++f) {
    for (int t=f+1; t<N; ++t) {
      sum += d[f][t];
    }
  }
  return sum;
}

void print(int v)
{
  string strval;
  strval = bitset<32>(v).to_string();
  int len=strval.length();
  bool valid = false;
  for (int i=0; i<len; ++i) {
    if (!valid && strval[i] == '0') continue;
    for (; i<len; ++i) {
      cout << strval[i];
    }
  }
  cout << endl;
}

int main() {
  input();
  print(solve());
  return 0;
}

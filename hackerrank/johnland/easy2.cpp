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
      if (d[f][k] == BIG) continue;
      for (int t=0; t<N; ++t) {
        if (f==t) continue;
        if (k==t) continue;
        if (d[k][t] == BIG) continue;
        if (d[f][k] + d[k][t] < d[f][t]) {
          if (f==0 && t==3) {
            cout << "UPDATE 0->3 " << d[f][t] << " " << d[f][k] << " " << d[k][t] << endl;
          }
          d[f][t] = d[f][k] + d[k][t];
        }
      }
    }

    cout << "========================= " << k << endl;
    for (int f=0; f<N; ++f) {
      for (int t=f+1; t<N; ++t) {
        cout << f << "->" << t << " = " << d[f][t] << endl;
      }
    }
  }

  int sum = 0;
  for (int f=0; f<N; ++f) {
    for (int t=f+1; t<N; ++t) {
      cout << f << "->" << t << " = " << d[f][t] << endl;
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

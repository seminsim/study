#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
vector<int> a;

void input()
{
  cin >> n;
  a.resize(n);
  for (int i=0; i<n; ++i) {
    cin >> a[i];
  }
}

tuple<int, int> solve()
{
  int s = 0;
  int m = -123456789;
  int cm = 0;
  int lm = 0;
  for (int i=0; i<n; ++i) {
    s += max(a[i], 0);
    m = max(m, a[i]);
    lm = max(lm+a[i], a[i]);
    cm = max(cm, lm);
  }

  return make_tuple(m < 0 ? m : s, m < 0 ? m : cm);
}

int main (int argc, char* argv[])
{
  int t;
  cin >> t;
  for (int i=0; i<t; ++i) {
    input();
    auto res = solve();
    cout << get<1>(res) << " " << get<0>(res) << endl;
  }

  return 0;
}

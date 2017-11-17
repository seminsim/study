#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

typedef long dt;

dt n, m;
vector<dt> c;
map< tuple<int, int>, dt > cache;

void input()
{
  cin >> n >> m;
  c.resize(m);
  for (int i=0; i<m; ++i) {
    cin >> c[i];
  }
}

dt solve(int tn, int ubi)
{
  dt cnt = 0;
  if (tn == 0) return 1;
  if (ubi == 0) return 0;
  if (cache.find( make_tuple(tn, ubi) ) != cache.end()) return cache[make_tuple(tn, ubi)];
  int mv = c[ubi-1];
  for (int i=0; i<=tn; i+=mv) {
    cnt += solve(tn - i, ubi-1);
  }
  cache[ make_tuple(tn, ubi) ] = cnt;
  return cnt;
}

int main (int argc, char* argv[])
{
  input();
  cout << solve(n, m) << endl;
  return 0;
}


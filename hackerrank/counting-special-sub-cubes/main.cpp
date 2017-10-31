#include <array>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

const int MAX_N = 50;

int n;
array<array<array<int, MAX_N>, MAX_N>, MAX_N> f;
array<array<array<int, MAX_N>, MAX_N>, MAX_N> m;

void input()
{
  cin >> n;
  for (int x=0; x<n; ++x) {
    for (int y=0; y<n; ++y) {
      for (int z=0; z<n; ++z) {
        cin >> f[x][y][z];
        m[x][y][z] = f[x][y][z];
      }
    }
  }
}

void solve()
{
  for (int k=0; k<n; ++k) {
    if (k > 0) {
      for (int x=0; x<n-k; ++x) {
        for (int y=0; y<n-k; ++y) {
          for (int z=0; z<n-k; ++z) {
            m[x][y][z] = f[x][y][z];
            m[x][y][z] = max(m[x][y][z], f[x+0][y+0][z+0]);
            m[x][y][z] = max(m[x][y][z], f[x+0][y+0][z+1]);
            m[x][y][z] = max(m[x][y][z], f[x+0][y+1][z+0]);
            m[x][y][z] = max(m[x][y][z], f[x+0][y+1][z+1]);
            m[x][y][z] = max(m[x][y][z], f[x+1][y+0][z+0]);
            m[x][y][z] = max(m[x][y][z], f[x+1][y+0][z+1]);
            m[x][y][z] = max(m[x][y][z], f[x+1][y+1][z+0]);
            m[x][y][z] = max(m[x][y][z], f[x+1][y+1][z+1]);
          }
        }
      }
    }

    int cnt = 0;
    for (int x=0; x<n-k; ++x) {
      for (int y=0; y<n-k; ++y) {
        for (int z=0; z<n-k; ++z) {
          if (m[x][y][z] == k+1) ++cnt;
        }
      }
    }
    cout << cnt << " ";

    swap(f, m);
  }
  cout << endl;
}

int main (int argc, char* argv[])
{
  int q;
  cin >> q;
  for (int i=0; i<q; ++i) {
    input();
    solve();
  }
  return 0;
}

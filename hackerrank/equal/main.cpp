#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int actionCount(vector<int>& n, int N, int min)
{
  int actions = 0;
  for (int i=0; i<N; ++i) {
    int d = n[i] - min;
    actions += d/5 + (((d%5)+1) / 2);
  }
  return actions;
}

int solve()
{
  int N;
  vector<int> n;
  int minN = 123456789;

  cin >> N;

  if (N==0) return 0;

  n.resize(N);
  for (int i=0; i<N; ++i) {
    cin >> n[i];
    minN = min(minN, n[i]);
  }

  int actions = actionCount(n, N, minN);
  actions = min(actions, actionCount(n, N, minN-1));
  actions = min(actions, actionCount(n, N, minN-2));
  actions = min(actions, actionCount(n, N, minN-3));
  actions = min(actions, actionCount(n, N, minN-4));
  actions = min(actions, actionCount(n, N, minN-5));

  return actions;
}

int main (int argc, char* argv[])
{
  int T;
  cin >> T;
  for (int i=0; i<T; ++i)
    cout << solve() << endl;
}

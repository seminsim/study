#include <cmath>
#include <cstdio>
#include <set>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int BIG = 123456789;

int N;
vector<int> d;
vector<int> sd;
vector< set<int> > edges;

void input()
{
  cin >> N;
  d.resize(N,0);
  sd.resize(N,0);
  for (int i=0; i<N; ++i) {
    cin >> d[i];
  }
  edges.resize(N);
  int n1, n2;
  for (int i=0; i<N-1; ++i) {
    cin >> n1 >> n2;
    edges[n1-1].insert(n2-1);
    edges[n2-1].insert(n1-1);
  }
}

int sumUp(int node, int parent)
{
  int sum = d[node];
  auto itEnd = edges[node].end();
  int childNode;
  for (auto it=edges[node].begin(); it!=itEnd; ++it) {
    childNode = *it;
    if (childNode == parent) continue;
    sum += (sd[childNode] = sumUp(childNode, node));
  }
  return sd[node] = sum;
}

int solve()
{
  sumUp(0, -1);
  int delta;
  int bestDelta = BIG;
  int bestNode = -1;
  for (int i=0; i<N; ++i) {
    delta = abs(sd[0] - sd[i] - sd[i]);
    if (delta < bestDelta) {
      bestDelta = delta;
      bestNode = i;
    }
  }
  return bestDelta;
}

int main() {
  input();
  cout << solve() << endl;
  return 0;
}

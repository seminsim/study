#include <cmath>
#include <cstdio>
#include <set>
#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
// depth, parent
vector<tuple<int,int> > s;
// weight, from, to
set<tuple<int,int,int> > e;

void input()
{
  int weight, from, to;
  cin >> N >> M;

  s.clear();
  s.resize(N, std::make_tuple(0, -1));

  for (int i=0; i<M; ++i) {
    cin >> from >> to >> weight;
    e.insert(tuple<int,int,int>(weight, from-1, to-1));
  }
}

int getSet(int n)
{
  int depth, parent;
  while (true) {
    tie(depth, parent) = s[n];
    if (parent < 0) return n;
    n = parent;
  }
}

void mergeSet(int a, int b)
{
  int depthA, parentA;
  int depthB, parentB;
  tie(depthA, parentA) = s[a];
  tie(depthB, parentB) = s[b];

  if (depthA == depthB) {
    s[a] = make_tuple(depthA+1, parentA);
    s[b] = make_tuple(depthB, a);

  } else if (depthA < depthB) {
    s[a] = make_tuple(depthA, b);

  } else if (depthA > depthB) {
    s[b] = make_tuple(depthB, a);

  }
}

int solve()
{
  int selectedEdges = 0;
  int totalWeight = 0;

  int weight, from, to;
  int setA, setB;
  while (!e.empty()) {
    auto it = e.begin();
    tie(weight, from, to) = *it;
    setA = getSet(from);
    setB = getSet(to);
    if (setA != setB) {
      // merge
      mergeSet(setA, setB);
      selectedEdges ++;
      totalWeight += weight;

      if (selectedEdges == N-1) return totalWeight;
    }

    e.erase(it);
  }

  return -1;
}

int main() {
  input();
  cout << solve() << endl;
    return 0;
}

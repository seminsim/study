#include <cmath>
#include <cstdio>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define DEBUG 0
#define ONDEBUG if(DEBUG)

const int UNLIMITED = 123456789;

int N, E;
vector<int> d;
vector< vector<int> > w;
set<int> visited;
set<int> reachable;

void input()
{
  cin >> N >> E;

  d.clear();
  d.resize(N, UNLIMITED);

  w.clear();
  w.resize(N);
  for (int i=0; i<N; ++i)
  {
    w[i].clear();
    w[i].resize(N, UNLIMITED);
  }

  int from, to, weight;
  for (int i=0; i<E; ++i) {
    cin >> from >> to >> weight;
    w[from-1][to-1] = weight;
    w[to-1][from-1] = weight;
  }

  visited.clear();
  reachable.clear();
}

int search()
{
  ONDEBUG cout << "search()" << endl;

  // init
  reachable.insert(0);
  d[0] = 0;
  ONDEBUG cout << "init with node 0" << endl;

  while (true) {
    // get min node
    int min = UNLIMITED;
    int minNode, cur_d;
    int curPathCost = d[N-1];
    for (auto it = reachable.begin(); it != reachable.end(); ++it) {
      cur_d = d[*it];
      if (cur_d >= curPathCost) continue;
      if (cur_d < min) {
        min = cur_d;
        minNode = *it;
      }
    }
    ONDEBUG cout << "getNode " << minNode << endl;

    // repeat or terminate
    if (min == UNLIMITED) break;
    ONDEBUG cout << "repeat" << endl;

    // update and expand
    int new_d;
    for (int i=0; i<N; ++i) {
      ONDEBUG cout << "lookup edge " << minNode << " to " << i << endl;
      if (w[minNode][i] == UNLIMITED) continue;
      ONDEBUG cout << "weight of edge " << minNode << " to " << i << " = " << w[minNode][i] << endl;
      if (visited.find(i) != visited.end()) continue;
      cur_d = d[i];
      new_d = max(min, w[minNode][i]);
      if (new_d < cur_d) d[i] = new_d;
      reachable.insert(i);
      ONDEBUG cout << "updateCost " << i << " with " << new_d << endl;
    }

    reachable.erase(minNode);
    visited.insert(minNode);
  }

  return d[N-1];
}

int main()
{
  input();
  int cost = search();
  if (cost == UNLIMITED) cout << "NO PATH EXISTS" << endl;
  else cout << cost << endl;

  return 0;
}

#include <cmath>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define DEBUG 0
#define ONDEBUG if(DEBUG)

#define SAFE 0
#define ONSAFE if(SAFE)

const int UNLIMITED = 123456789;

int N, E;
vector<int> d;
map<int, map<int, int> > w;
set<int> visited;
map<int, set<int> > reachable;

void input()
{
  cin >> N >> E;

  d.clear();
  d.resize(N, UNLIMITED);

  w.clear();
  int from, to, weight;
  for (int i=0; i<E; ++i) {
    cin >> from >> to >> weight;
    w[from-1][to-1] = weight;
    w[to-1][from-1] = weight;
  }

  visited.clear();
  reachable.clear();
}

void erase(int d, int i)
{
  ONSAFE if (reachable.find(d) == reachable.end()) return;
  ONSAFE if (reachable[d].find(i) == reachable[d].end()) return;
  if (reachable[d].size() == 1) {
    reachable.erase(d);
  } else {
    reachable[d].erase(i);
  }
}

int search()
{
  ONDEBUG cout << "search()" << endl;

  // init
  reachable[0].insert(0);
  d[0] = 0;
  ONDEBUG cout << "init with node 0" << endl;

  while (true) {
    // get min node
    int min = UNLIMITED;
    int minNode;

    if (reachable.empty()) break;

    auto minReachableSetIt = reachable.begin();
    auto minSet = minReachableSetIt->second;
    auto pickedIt = minSet.begin();

    min = minReachableSetIt->first;
    minNode = *pickedIt;

    ONDEBUG cout << "getNode " << minNode << endl;

    // repeat or terminate
    if (min == UNLIMITED) break;
    ONDEBUG cout << "repeat" << endl;

    // update and expand
    int cur_d, new_d, to, cur_w;
    auto begin = w[minNode].begin();
    auto end = w[minNode].end();
    auto visited_end = visited.end();
    for (auto it = begin; it!=end; ++it) {
      to = it->first;
      cur_w = it->second;

      ONDEBUG cout << "weight of edge " << minNode << " to " << to << " = " << cur_w << endl;

      if (visited.find(to) != visited_end) continue;
      cur_d = d[to];
      new_d = max(min, cur_w);
      if (new_d < cur_d) {
        d[to] = new_d;
        ONDEBUG cout << "updateCost " << to << " with " << new_d << endl;

        if (cur_d != UNLIMITED) erase(cur_d, to);
        reachable[new_d].insert(to);
      }
    }

    erase(min, minNode);
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

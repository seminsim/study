#include <sys/stat.h>
#include <unistd.h>
#include <cmath>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int UNLIMITED = 123456789;

char data[10000000];

int N, E;
vector<int> d;
map<int, map<int, int> > w;
vector<bool> visited;
set< pair<int,int> > reachable;

void input()
{
  struct stat sb;
  int rc = ::fstat( STDIN_FILENO, &sb );

  // use C-style calloc() to get memory that's been
  // set to zero as calloc() is often optimized to be
  // faster than a new followed by a memset().
  size_t totalRead = 0UL;
  while ( totalRead  < sb.st_size )
  {
      ssize_t bytesRead = ::read( STDIN_FILENO,
          data + totalRead, sb.st_size - totalRead );
      if ( bytesRead <= 0 )
      {
          break;
      }
      totalRead += bytesRead;
  }

  char *next;
  N = ::strtol( data, &next, 0 );
  E = ::strtol( next, &next, 0 );

  d.clear();
  d.resize(N, UNLIMITED);

  w.clear();
  int from, to, weight;
  for (int i=0; i<E; ++i) {
    from = ::strtol( next, &next, 0 );
    to = ::strtol( next, &next, 0 );
    weight = ::strtol( next, &next, 0 );

    w[from-1][to-1] = weight;
    w[to-1][from-1] = weight;
  }

  visited.clear();
  visited.resize(N, false);
  reachable.clear();
}

int search()
{
  // init
  reachable.insert(pair<int,int>(0, 0));
  d[0] = 0;

  while (true) {
    // get min node
    int min = UNLIMITED;
    int minNode;

    // terminate?
    if (reachable.empty()) break;

    auto minReachableSetIt = reachable.begin();

    min = minReachableSetIt->first;
    minNode = minReachableSetIt->second;

    if (min >= d[N-1]) break;

    // update and expand
    int cur_d, new_d, to, cur_w;
    auto begin = w[minNode].begin();
    auto end = w[minNode].end();
    for (auto it = begin; it!=end; ++it) {
      to = it->first;
      cur_w = it->second;

      if (visited[to]) continue;

      cur_d = d[to];
      new_d = max(min, cur_w);
      if (new_d < cur_d) {
        d[to] = new_d;

        if (cur_d != UNLIMITED) reachable.erase(pair<int,int>(cur_d, to));
        if (new_d < d[N-1]) reachable.insert(pair<int,int>(new_d, to));
      }
    }

    reachable.erase(pair<int,int>(min, minNode));
    visited[minNode] = true;
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

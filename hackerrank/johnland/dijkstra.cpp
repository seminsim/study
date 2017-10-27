#include <map>
#include <list>
#include <set>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

#define DEBUG 0
#define ONDEBUG if(DEBUG)

typedef long long i64;

const i64 BIG = 123456789;
const i64 SEPERATOR = 1000000;

int N, M;
vector< pair<int, int> > e; // edge
vector< list<int> > es;  // edge set
map<int, map<int, int> > ew;  // edge weight

void input()
{
  cin >> N >> M;
  e.resize(M);
  es.resize(N);
  int f, t, w;
  for (int i=0; i<M; ++i) {
    cin >> f >> t >> w;
    f--; t--;
    e[w] = make_pair(min(f,t), max(f,t));
    es[f].push_back(w);
    es[t].push_back(w);
    ew[f][t] = w;
    ew[t][f] = w;
  }
}

void solve()
{
  vector<int> ec(M); // edge count

  vector<int> d(N);  // distance
  vector<int> p(N);  // parent
  vector<bool> visited(N); // visited
  set<i64> q; // priority queue, <cost, node>

  for (int s=0; s<N-1; ++s) {
    // dijkstra
    fill(d.begin(), d.end(), BIG);
    d[s] = 0;
    fill(p.begin(), p.end(), -1);
    fill(visited.begin(), visited.end(), false);
    q.clear();
    for (int i=0; i<N; ++i) q.insert(i==s ? i : BIG * SEPERATOR + i);

    ONDEBUG cout << "== Dijkstra from node " << s << endl;
    while (true) {
      if (q.empty()) break;

      // pick closest reachable
      auto it = q.begin();
      int currentNodeCost = *it / SEPERATOR;
      int currentNodeId = *it % SEPERATOR;

      ONDEBUG cout << "Node " << currentNodeId << " cost=" << currentNodeCost << endl;

      // update neighr cost, parent, reachability
      for (auto& w : es[currentNodeId]) {
        int f = e[w].first; // edge from
        int t = e[w].second; // edge to

        int nv;
        nv = (f==currentNodeId ? t : f);
        if (visited[nv]) continue;

        ONDEBUG cout << "  > Update " << nv << " cost=" << currentNodeCost << " " << w << " cmp " << d[nv] << endl;

        int newNeighborD = max(currentNodeCost, w);
        if (newNeighborD < d[nv]) {
          q.erase(d[nv] * SEPERATOR + nv);
          d[nv] = newNeighborD;
          p[nv] = currentNodeId;
          q.insert(newNeighborD * SEPERATOR + nv);
        }
      }

      // mark this as visited
      q.erase(it);
      visited[currentNodeId] = true;
    }

    // count up nodes
    for (int t=s+1; t<N; ++t) {
      int currentNode = t;
      int parentNode;
      while (true) {
        parentNode = p[currentNode];
        if (parentNode < 0) break;

        int ew_cp = ew[currentNode][parentNode];
        if (ew_cp == (int)BIG) break;
        ec[ew_cp] ++;
        currentNode = parentNode;
      }
    }
  }

  stack<int> st;
  int pos = 0;
  int current, next;
  next = ec[pos];
  while (true) {
    current = next;
    next = current/2 + (pos<M-1 ? ec[pos+1] : 0);
    st.push(current%2);
    if (pos>=M-1 && next == 0) break;
    ++pos;
  }

  while (st.top() == 0) st.pop();
  while (!st.empty()) {
    cout << st.top();
    st.pop();
  }
  cout << endl;
}

int main() {
  input();
  solve();
  return 0;
}

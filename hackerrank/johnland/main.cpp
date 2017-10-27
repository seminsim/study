#include <map>
#include <list>
#include <set>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

#define DEBUG 0
#define ONDEBUG if(DEBUG)

typedef long long dt;

dt N, M;
vector< pair<dt, dt> > e; // edge [w] = <u, v>
map<dt, map<dt, dt> > ew;  // edge weight [u][v] = w

vector< pair<dt, dt> > p; // parent for set grouping
vector< list<dt> > nv;  // neighbor
vector<dt> ec; // edge count

void input()
{
  cin >> N >> M;
  e.resize(M);
  dt f, t, w;
  for (dt i=0; i<M; ++i) {
    cin >> f >> t >> w;
    f--; t--;

    e[w] = make_pair(min(f,t), max(f,t));

    if (ew.find(f) != ew.end() &&
      ew[f].find(t) != ew[f].end() &&
      ew[f][t] < w)
      continue; // duplicated

    ew[f][t] = w;
    ew[t][f] = w;
  }

  p.resize(N, pair<dt, dt>(-1, 0));
  nv.resize(N);
  ec.resize(M);
}

dt getSetId(dt v)
{
  while (p[v].first >= 0) v = p[v].first;
  return v;
}

void unionSet(dt u, dt v)
{
  while (p[u].first >= 0) u = p[u].first;
  while (p[v].first >= 0) v = p[v].first;
  if (p[u].second < p[v].second) {
    p[u].first = v;
  } else if (p[u].second > p[v].second) {
    p[v].first = u;
  } else {
    p[u].first = v;
    p[v].second++;
  }
}

dt edgeCountUp(dt v, dt parent)
{
  dt totalChildCount = 0;
  dt childCount = 0;
  for (auto& n : nv[v]) {
    if (n == parent) continue;
    childCount = edgeCountUp(n, v);
    ONDEBUG cout << "EDGE COUNT " << N << " " << childCount << " at " << v << " " << n << " w=" << ew[v][n] << endl;
    ec[ ew[v][n] ] = (N - childCount) * childCount;
    ONDEBUG cout << ec[ ew[v][n] ] << endl;
    totalChildCount += childCount;
  }
  return totalChildCount + 1;
}

void prdtResult()
{
  ONDEBUG {
    cout << "[EDGE count]" << endl;
    for (dt i=0; i<M; ++i) {
      cout << i << " " << ec[i] << endl;
    }
  }

  stack<dt> st;
  dt pos = 0;
  dt current, next;
  next = ec[pos];
  while (true) {
    current = next;
    next = current/2 + (pos+1<M ? ec[pos+1] : 0);
    ONDEBUG cout << "STACK PUSH " << current%2 << endl;
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

void solve()
{
  // build MST
  dt selectedEdgeCount = 0;
  for (dt i=0; i<M && selectedEdgeCount<N-1; ++i) {
    dt u, v;
    u = e[i].first;
    v = e[i].second;
    if (getSetId(u) == getSetId(v)) continue;

    ONDEBUG cout << "Select edge " << i << " from " << u << " to " << v << endl;
    selectedEdgeCount++;
    nv[u].push_back(v);
    nv[v].push_back(u);
    unionSet(u,v);
  }

  // count edges
  edgeCountUp(0, -1);
}

int main() {
  input();
  solve();
  prdtResult();

  return 0;
}

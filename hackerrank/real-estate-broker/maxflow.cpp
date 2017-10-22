#include <queue>
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

const int BIG = 123456789;


int N, M; // N: # of clients, M: # of houses
vector< tuple<int, int> > ap; // a: min area of client i, p: max price of client i
vector< tuple<int, int> > xy; // x: area of house j, y: min price of house j

int V;
vector< vector<int> > flow;

vector<bool> visited;
vector<int> parent;

void input()
{
  cin >> N >> M;
  ap.resize(N);
  xy.resize(M);

  V = 2 + N + M;
  flow.resize(V, vector<int>(V));
  visited.resize(V);
  parent.resize(V);

  for (int i=0; i<N; ++i) {
    int a, p;
    cin >> a >> p;
    ap[i] = make_tuple(a, p);
  }

  for (int i=0; i<M; ++i) {
    int x, y;
    cin >> x >> y;
    xy[i] = make_tuple(x, y);
  }
}

void make_graph()
{
  // s to clients
  for (int i=0; i<N; ++i) {
    flow[0][1+i] = 1;
  }
  // houses to t
  for (int j=0; j<M; ++j) {
    flow[1+N+j][V-1] = 1;
  }
  for (int i=0; i<N; ++i) {
    int a, p;
    tie(a, p) = ap[i];
    for (int j=0; j<M; ++j) {
      int x, y;
      tie(x, y) = xy[j];
      if (a <= x && p >= y) flow[1+i][1+N+j] = 1;
    }
  }
}

bool findPathBFS()
{
  fill(visited.begin(), visited.end(), false);
  fill(parent.begin(), parent.end(), -1);

  queue<int> q;
  int current;

  q.push(0);
  visited[0] = true;
  while(!q.empty()) {
    current = q.front();
    q.pop();
    for (int i=0; i<V; ++i) {
      if (!visited[i] && flow[current][i] > 0){
        q.push(i);
        parent[i] = current;
      }
    }
    visited[current] = true;
  }

  return visited[V-1];
}

int solve()
{
  make_graph();

  int current;
  int maxBackflow;
  while (true) {
    bool pathFound = findPathBFS();
    if (!pathFound) break;

    maxBackflow = BIG;
    current = V-1;
    while (current != 0) {
      maxBackflow = min(flow[parent[current]][current], maxBackflow);
      current = parent[current];
    }

    current = V-1;
    while (current != 0) {
      flow[parent[current]][current] -= maxBackflow;
      flow[current][parent[current]] += maxBackflow;
      current = parent[current];
    }
  }

  int total = 0;
  for (int i=0; i<V; ++i) {
    total += flow[V-1][i];
  }

  return total;
}

int main (int argc, char* argv[])
{
  input();
  cout << solve() << endl;

  return 0;
}

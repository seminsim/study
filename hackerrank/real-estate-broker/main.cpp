#include <queue>
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

const int BIG = 1234567890;


int N, M; // N: # of clients, M: # of houses
vector< tuple<int, int> > ap; // a: min area of client i, p: max price of client i
vector< tuple<int, int> > xy; // x: area of house j, y: min price of house j

int V;
vector< vector<int> > flow;

vector<bool> visited;
vector<int> parent;

vector< int > client2houseCount;
vector< vector<int> > client2house;
vector< int > house2clientCount;
vector< vector<int> > house2client;

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

  // for fast lookup
  client2houseCount.resize(N, 0);
  client2house.resize(N, vector<int>(M, 0));
  house2clientCount.resize(M, 0);
  house2client.resize(M, vector<int>(N, 0));
  for (int i=0; i<N; ++i) {
    for (int j=0; j<M; ++j) {
      if (flow[1+i][1+N+j] == 1) {
        client2house[i][client2houseCount[i]++] = j;
        house2client[j][house2clientCount[j]++] = i;
      }
    }
  }
}

inline bool isClient(int i)
{
  return (i > 0 && i < N+1);
}

inline bool isHouse(int i)
{
  return (i > N && i < N+M+1);
}

bool findPathBFS(int clientId)
{
  fill(visited.begin(), visited.end(), false);
  fill(parent.begin(), parent.end(), -1);

  queue<int> q;
  int current;

  parent[1+clientId] = 0;
  q.push(1+clientId);
  while(!q.empty()) {
    current = q.front();
    q.pop();
    if (isClient(current)) {
      // client to house
      int clientId = current-1;
      int cnt = client2houseCount[clientId];
      for (int k=0; k<cnt; ++k) {
        int i = 1+N+client2house[clientId][k];
        if (!visited[i] && flow[current][i] > 0){
          // client to house to target
          if (flow[i][V-1] > 0) {
            parent[i] = current;
            parent[V-1] = i;
            return true;
          // client to house to client
          } else {
            q.push(i);
            parent[i] = current;
          }
        }
      }
    } else if (isHouse(current)) {
      // house to client
      int houseId = current-1-N;
      int cnt = house2clientCount[houseId];
      for (int k=0; k<cnt; ++k) {
        int i = 1+house2client[houseId][k];
        if (!visited[i] && flow[current][i] > 0){
          q.push(i);
          parent[i] = current;
        }
      }
    }
    visited[current] = true;
  }

  return false;
}

int solve()
{
  make_graph();

  int current;
  int maxBackflow;
  int total = 0;
  for (int i=0; i<N; ++i) {
    if (!findPathBFS(i)) continue;
    current = V-1;
    while (current != 0) {
      flow[parent[current]][current] --;
      flow[current][parent[current]] ++;
      current = parent[current];
    }
    total ++;
  }

  return total;
}

int main (int argc, char* argv[])
{
  input();
  cout << solve() << endl;

  return 0;
}

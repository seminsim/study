#include <list>
#include <tuple>
#include <vector>
#include <iostream>

#define DEBUG 0
#define ONDEBUG if(DEBUG)

using namespace std;

typedef long long int dt;
typedef tuple<dt, dt, dt, dt> NodeState;

const dt MOD_DIVIEND = 1000000007;

int N;
vector< list<int> > neighbor;

void input()
{
  cin >> N;
  neighbor.resize(N);
  for (int i=0; i<N-1; ++i){
    int f, t;
    cin >> f >> t;
    neighbor[f-1].push_back(t-1);
    neighbor[t-1].push_back(f-1);
  }
}

NodeState nodeCases(int nodeId, int parentId = -1)
{
  int size = neighbor[nodeId].size() + (parentId < 0 ? 1 : 0);

  ONDEBUG cout << "node " << nodeId << " size=" << size << endl;
  if (size == 1) {
    ONDEBUG cout << "node " << nodeId << " (1,0,1,0)" << endl;
    return make_tuple(1,0,1,0);
  }

  list<NodeState> childrenStates;

  auto it = neighbor[nodeId].begin();
  auto itEnd = neighbor[nodeId].end();
  for (; it!=itEnd; ++it) {
    if (*it == parentId) continue;
    childrenStates.push_back( nodeCases(*it, nodeId) );
  }

  dt Cri, Crc, Cbi, Cbc;
  Cri = Crc = Cbi = Cbc = 1;
  for (auto& tp : childrenStates){
    Cri *= get<3>(tp);
    Crc *= get<0>(tp) + get<1>(tp) + get<3>(tp);
    Cbi *= get<1>(tp);
    Cbc *= get<1>(tp) + get<2>(tp) + get<3>(tp);

    Cri %= MOD_DIVIEND;
    Crc %= MOD_DIVIEND;
    Cbi %= MOD_DIVIEND;
    Cbc %= MOD_DIVIEND;
  }
  Crc += MOD_DIVIEND - Cri;
  Cbc += MOD_DIVIEND - Cbi;

  ONDEBUG cout << "node " << nodeId << " (" << Cri << "," << Crc << "," << Cbi << "," << Cbc << ")" << endl;

  return make_tuple(
    Cri % MOD_DIVIEND,
    Crc % MOD_DIVIEND,
    Cbi % MOD_DIVIEND,
    Cbc % MOD_DIVIEND
    );
}

dt solve()
{
  dt Tri, Trc, Tbi, Tbc;
  tie(Tri, Trc, Tbi, Tbc) = nodeCases(0);
  return (Trc + Tbc) % MOD_DIVIEND;
}

int main (int argc, char* argv[])
{
  input();
  cout << solve() << endl;
  return 0;
}

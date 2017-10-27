#include <vector>
#include <iostream>

using namespace std;

typedef long long dt;

const dt MOD_DIVIEND = 1000000007;

int N;
vector<dt> data;

void input()
{
  cin >> N;
  data.resize(N);
  for (int i=0; i<N; ++i) {
    cin >> data[i];
  }
}

dt timesmod( dt x, dt y, dt m )
{
  x %= m;
  y %= m;
  dt a = x < y ? x : y; // min
  dt b = x < y ? y : x; // max
  dt product = 0;
  for (; a != 0; a >>= 1, b = (b+b)%m )
    if (a&1) product = (product+b)%m);
  return product;
}

dt solve()
{
  dt d, D, Ec, Et, S;
  dt d_next, D_next, Ec_next, Et_next, S_next;
  d = data[0];
  D = 3 * d;
  Ec = 5;
  Et = 11 * d;
  S = 29 * d;

  for (int i=1; i<N; ++i) {
    d = data[i];

    D_next = 2*D + 3*d;
    Ec_next = 4*Ec + 5;
    Et_next = 4*Et + (3*Ec+5)*D + (8*Ec+11)*d;
    S_next = 4*S + (16*timesmod(Ec, Ec, MOD_DIVIEND) + 44*Ec + 29)*d + 12*timesmod(Ec, Et, MOD_DIVIEND) + 20*Et;

    D = D_next % MOD_DIVIEND;
    Ec = Ec_next % MOD_DIVIEND;
    Et = Et_next % MOD_DIVIEND;
    S = S_next % MOD_DIVIEND;
  }

  return S;
}

int main (int argc, char* argv[])
{
  input();
  cout << solve() << endl;
  return 0;
}

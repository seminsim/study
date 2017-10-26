#include <string>
#include <iostream>

using namespace std;

typedef long long dt;

const dt MOD_DIVIEND = 1e9+7;


string N;

void input()
{
  cin >> N;
}

dt solve()
{
  int size = N.length();
  dt totalSum, lastSum;
  totalSum = lastSum = (dt)(N[0] - '0');
  int lastD = 0;
  dt sum = 0;
  for (int i=1; i<size; ++i) {
    int d = (int)(N[i] - '0');
    sum = (lastSum + lastD) * 10 + (i * d);
    sum %= MOD_DIVIEND;

    totalSum += sum + d;
    lastSum = sum;
    lastD = d;
    totalSum %= MOD_DIVIEND;
  }

  return totalSum;
}

int main (int argc, char* argv[])
{
  input();
  cout << solve() << endl;
  return 0;
}

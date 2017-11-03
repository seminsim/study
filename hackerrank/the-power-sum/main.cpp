#include <cmath>
#include <map>
#include <tuple>
#include <iostream>

using namespace std;

int X;
int N;
map< tuple<int,int>, int> cachedResult;

void input()
{
  cin >> X >> N;
}

int solve(int X, int C)
{
  if (X<0) return 0;
  if (X==1) return 1;
  if (cachedResult.find(make_tuple(X,C)) != cachedResult.end())
    return cachedResult[make_tuple(X,C)];

  int maxE = 0;
  while (pow(maxE, N) < X) ++maxE;

  int sumCases = 0;
  if (pow(maxE, N) == X && maxE<C) ++sumCases;
  for (int e = min(maxE-1, C-1); e>1; --e) {
    int es = pow(e, N);
    sumCases += solve(X - es, e);
  }

  cachedResult[make_tuple(X,C)] = sumCases;
  return sumCases;
}

int main (int argc, char* argv[])
{
  input();
  cout << solve(X, X) << endl;
  return 0;
}

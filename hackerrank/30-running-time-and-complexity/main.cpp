#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

const int NOT_PRIME = 0;
const int PRIME = 1;
const string Answers[] = {"Not prime", "Prime"};

string solve(long N)
{
  if (N == 1) return Answers[NOT_PRIME];
  if (N == 2) return Answers[PRIME];
  if (N%2 == 0) return Answers[NOT_PRIME];

  for (long i=3; i*i<=N; i+=2) {
    if (N % i == 0) return Answers[NOT_PRIME];
  }

  return Answers[PRIME];
}

int main (int argc, char* argv[])
{
  int T;
  long N;
  cin >> T;
  for (int i=0; i<T; ++i) {
    cin >> N;
    cout << solve(N) << endl;
  }
  return 0;
}

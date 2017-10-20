#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int N;
vector<int> A;
vector<int> B;
vector<int> maxTop;
vector<int> maxBottom;

void input()
{
  cin >> N;
  A.resize(N);
  B.resize(N);
  maxTop.resize(N);
  maxBottom.resize(N);
  for (int i=0; i<N; ++i) {
    cin >> B[i];
  }
}

int solve()
{
  maxTop[0] = 0;
  maxBottom[0] = 0;
  int valueTop1, valueTop2;
  int valueBottom1, valueBottom2;
  for (int i=1; i<N; ++i) {
    valueTop1 = maxTop[i-1] + abs(B[i] - B[i-1]);
    valueTop2 = maxBottom[i-1] + B[i] - 1;
    maxTop[i] = max(valueTop1, valueTop2);

    valueBottom1 = maxTop[i-1] + B[i-1] - 1;
    valueBottom2 = maxBottom[i-1];
    maxBottom[i] = max(valueBottom1, valueBottom2);
  }
  return max(maxTop[N-1], maxBottom[N-1]);
}

int main (int argc, char* argv[])
{
  int C;
  cin >> C;
  for (int i=0; i<C; ++i) {
    input();
    cout << solve() << endl;
  }
  return 0;
}

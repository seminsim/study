#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

int N;
vector<int> s;
vector<int> l;

void input()
{
  cin >> N;
  s.resize(N);
  l.resize(N);
  for (int i=0; i<N; ++i) {
    int snum;
    cin >> snum;
    s[i] = snum-1;
    l[s[i]] = i;
  }
}

bool isTooChaotic()
{
  for (int i=0; i<N; ++i) {
    if (i - l[i] > 2) return true;
  }
  return false;
}

int solve()
{
  int count = 0;
  for (int i=0; i<N; ++i) {
    if (l[i] < i) {
      while (l[i] != i) {
        int loc = l[i];
        l[i]++;
        l[s[loc+1]]--;
        swap(s[loc], s[loc+1]);
        ++count;
      }
    }else {
      while (l[i] != i) {
        int loc = l[i];
        l[i]--;
        l[s[loc-1]]++;
        swap(s[loc], s[loc-1]);
        ++count;
      }
    }
  }
  return count;
}

int main (int argc, char* argv[])
{
  int T;
  cin >> T;
  for (int i=0; i<T; ++i) {
    input();
    if (isTooChaotic())
      cout << "Too chaotic" << endl;
    else
      cout << solve() << endl;
  }
  return 0;
}

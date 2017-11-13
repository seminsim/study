#include <set>
#include <tuple>
#include <iostream>

using namespace std;

long N;
set< tuple<long, long> > p;

void input()
{
  cin >> N;
  for (long i=0; i<N; ++i) {
    long pi;
    cin >> pi;
    p.insert(make_tuple(pi, i));
  }
}

long solve()
{
  long minLoss = 1234567890123456L;

  auto it = p.cbegin();
  const auto& it_end = p.cend();
  const auto& it_rend = p.crend();
  it++;
  for (; it != it_end; ++it) {
    const long& pi = get<0>(*it);
    const long& i = get<1>(*it);

    set< tuple<long, long> >::reverse_iterator it2(it);
    for (; it2 != it_rend; ++it2) {
      const long& pi2 = get<0>(*it2);
      const long& i2 = get<1>(*it2);
      if (pi - pi2 >= minLoss) break;
      if (i2 < i) continue;
      minLoss = min (minLoss, pi - pi2);
      break;
    }
  }
  return minLoss;
}

int main (int argc, char* argv[])
{
  input();
  cout << solve() << endl;
  return 0;
}

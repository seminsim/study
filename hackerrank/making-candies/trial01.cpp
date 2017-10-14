#include <bits/stdc++.h>

using namespace std;

const int BIG = 123456789;

void maxPerformance(long m, long w, long p, long a, long& newM, long& newW, long& newPerformance)
{
  if (m < w) {
    long mAdd = min(w-m, a);
    m += mAdd;
    a -= mAdd;
  } else if (m > w) {
    long wAdd = min(m-w, a);
    w += wAdd;
    a -= wAdd;
  }

  long halfA = a / 2;
  m += a - halfA;
  w += halfA;

  newM = m;
  newW = w;
  newPerformance = newM * newW;
}

long minPasses(long m, long w, long p, long n, long c, long s)
{
  long nextC = c + (m * w);
  if (nextC >= n) return s+1;

  long a = nextC / p;
  long newM, newW, newPerformance;
  maxPerformance(m, w, p, a, newM, newW, newPerformance);

  long keepStep = BIG;
  if (p * a > newPerformance - (m*w)) { // possibly better to keep
    keepStep = minPasses(m, w, p, n, nextC, s+1);
  }
  return min(keepStep, minPasses(newM, newW, p, n, nextC-(p*a), s+1));
}

long minimumPasses(long m, long w, long p, long n) {
    // Complete this function
    return minPasses(m, w, p, n, 0, 0);
}

int main() {
    long m;
    long w;
    long p;
    long n;
    cin >> m >> w >> p >> n;
    long result = minimumPasses(m, w, p, n);
    cout << result << endl;
    return 0;
}

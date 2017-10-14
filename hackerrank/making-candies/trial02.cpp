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

long minimumPasses(long m, long w, long p, long n) {
    // Complete this function
    long s = 1;
    long c = 0;
    long newC;
    long maxA;
    long newM, newW, newPerformance;
    while (true) {
      newC = c + (m * w);
      if (newC >= n) return s;

      maxA = newC / p;
      for (int a=0; a<maxA; ++a) {
        maxPerformance(m, w, p, a, newM, newW, newPerformance);
        if (newC - (p*a) + newPerformance >= n) return s+1;
      }

      maxPerformance(m, w, p, maxA, newM, newW, newPerformance);
      c = newC - (p * maxA);
      m = newM;
      w = newW;
      s++;
    }
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

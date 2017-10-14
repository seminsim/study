#include <bits/stdc++.h>

using namespace std;

typedef long long dt;

#define DEBUG 0
#define ONDEBUG if(DEBUG)

const dt BIG = numeric_limits<dt>::max();

inline dt keepSteps(dt s, dt n, dt c, dt performance)
{
  return s + 1 + ((n - c - 1) / (performance));
}

void maxPerformance(dt m, dt w, dt p, dt a, dt& newM, dt& newW, dt& newPerformance)
{
  if (m < w) {
    dt mAdd = min(w-m, a);
    m += mAdd;
    a -= mAdd;
  } else if (m > w) {
    dt wAdd = min(m-w, a);
    w += wAdd;
    a -= wAdd;
  }

  dt halfA = a / 2;
  m += (a - halfA);
  w += halfA;

  newM = m;
  newW = w;
  newPerformance = newM * newW;
}

dt minimumPasses(dt m, dt w, dt p, dt n) {
    // Complete this function
    dt minS = BIG;
    dt s = 0;
    dt keepS;
    dt c = 0;
    dt newC;
    dt maxA;
    dt newM, newW, performance, newPerformance;
    while (true) {
      if (s >= minS) return minS;
      performance = m * w;
      newC = c + performance;
      maxA = newC / p;
      ONDEBUG cout
        << " m=" << m
        << " w=" << w
        << " c=" << newC
        << " maxA=" << maxA
        << " s=" << s
        << " minS=" << minS
        << endl;

      if (m > 0 && performance / m != w) return s+1; // overflow, big enough
      //if (m*w > 0 && ((m*w) < m || (m*w) < w)) return s+1; // overflow, big enough
      if (newC < c) return s+1; // overflow, big enough
      if (newC >= n) return s+1; // goal reached

      for (dt a=(m >= p || w >= p) ? maxA : 0; a<=maxA; ++a) {
        ONDEBUG cout << " CHECK a=" << a << endl;
        if (a == 0) {
          newM = m;
          newW = w;
          newPerformance = performance = m * w;
          if (newPerformance == 0) continue; // no progress available
        } else {
          maxPerformance(m, w, p, a, newM, newW, newPerformance);
          if (newM > 0 && newPerformance / newM != newW) return s+2; // overflow, big enough
          if (newPerformance - performance >= p * a && a != maxA) {
            maxPerformance(m, w, p, a, newM, newW, newPerformance);

            a = maxA -1;
            continue;
          }
          //if (newM < m || newW < w) return s+1; // overflow, big enough
          //if (newPerformance < performance) return s+1; // overflow, big enough
        }
        keepS = keepSteps(s+1, n, newC - (p*a), newPerformance);
        if (keepS < minS) minS = keepS;
      }

      if (maxA == 0) {
        dt minWait = 1 + ((p-newC-1) / performance);
        c = newC + ((minWait - 1) * performance);
        s += minWait;
        continue;
      }

      c = newC - (p * maxA);
      m = newM;
      w = newW;
      s++;
    }
}

int main() {
    dt m;
    dt w;
    dt p;
    dt n;
    cin >> m >> w >> p >> n;
    dt result = minimumPasses(m, w, p, n);
    cout << result << endl;
    return 0;
}

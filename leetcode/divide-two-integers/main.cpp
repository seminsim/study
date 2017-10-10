
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

int divide (int dividend, int divisor)
{
  if (dividend == 0) return 0;
  if (dividend == divisor) return 1;
  if (divisor == 1) return dividend;
  if (dividend == INT_MIN && divisor == -1) return INT_MAX;
  if (divisor == -1) return -dividend;
  if (divisor == 0) return INT_MAX;

  int result = 0;
  bool isNegative = (dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0);

  int add1 = 0;
  if (divisor == INT_MIN) return 0;
  divisor = (divisor < 0) ? -divisor : divisor;
  if (dividend == INT_MIN) { dividend=INT_MAX-divisor+1; add1=1; }
  dividend = (dividend < 0) ? -dividend : dividend;

  int shift = 0;
  int shifted = divisor;
  while (true) {
    shift ++;
    shifted = divisor << shift;
    if (shifted < 0){
      shift --;
      break;
    }
    if (shifted >= dividend) break;
  }

  while (shift >= 0) {
    shifted = (divisor << shift);
    if (dividend >= shifted) {
      dividend -= shifted;
      result = (result << 1) + 1;
    } else {
      result = result << 1;
    }
    shift --;
  }

  return isNegative ? -(result+add1) : (result+add1);
}

int main (int argc, char* argv[])
{
  cout << divide (atoi(argv[1]), atoi(argv[2])) << endl;
}

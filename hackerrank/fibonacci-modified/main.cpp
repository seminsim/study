#include <cmath>
#include <array>
#include <iostream>
#include <iomanip>

using namespace std;

typedef unsigned long long int dt;
const int MAX_CAPACITY = 10000000;
const int ROUND_UP_THRESHOLD_POW = 5;
const dt ROUND_UP_THRESHOLD = 1e5;

struct BIGINT {
  array<dt, MAX_CAPACITY> data;
  int maxDigit;

  BIGINT() {data.fill(0); maxDigit=0;}
  BIGINT(BIGINT& rhs) {data=rhs.data; maxDigit=rhs.maxDigit;}
  BIGINT(BIGINT&& rhs) {data=move(rhs.data); maxDigit=rhs.maxDigit;}
  BIGINT& operator=(BIGINT&& rhs) {
    data=move(rhs.data); maxDigit=rhs.maxDigit;
    return *this;
  }
};

BIGINT t1;
BIGINT t2;
BIGINT t3;

int n;

void bi_fixup(BIGINT& num)
{
  dt roundedUp, nextRoundUp;
  roundedUp = 0;
  int newMaxDigit = 0;
  for (int i=0; i<num.maxDigit || roundedUp > 0; ++i){
    nextRoundUp = (num.data[i] + roundedUp) / ROUND_UP_THRESHOLD;
    num.data[i] = (num.data[i] + roundedUp) % ROUND_UP_THRESHOLD;
    roundedUp = nextRoundUp;
    if (roundedUp > 0) num.maxDigit = max(num.maxDigit, i+2);
  }
}

void bi_add(BIGINT& lhs, BIGINT& rhs1, BIGINT& rhs2)
{
  int newMaxDigit = max(rhs1.maxDigit, rhs2.maxDigit);
  for (int i=0; i<newMaxDigit; ++i){
    lhs.data[i] = rhs1.data[i] + rhs2.data[i];
  }
  lhs.maxDigit = newMaxDigit;
  bi_fixup(lhs);
}

void bi_mul(BIGINT& lhs, BIGINT& rhs1, BIGINT& rhs2)
{
  lhs.data.fill(0);
  lhs.maxDigit = 0;
  for (int i=0; i<rhs1.maxDigit; ++i){
    for (int j=0; j<rhs2.maxDigit; ++j){
      lhs.data[i+j] += rhs1.data[i] * rhs2.data[j];
      if (lhs.data[i+j] > 0) lhs.maxDigit = max(lhs.maxDigit, i+j+1);
    }
    bi_fixup(lhs);
  }
}

void print(const BIGINT& num)
{
  for (int i=num.maxDigit-1; i>=0; --i) {
    if (i==num.maxDigit-1)
      cout << num.data[i];
    else
      cout << setfill('0') << setw(ROUND_UP_THRESHOLD_POW) << num.data[i];
  }
  cout << endl;
}

void input()
{
  cin >> t1.data[0] >> t2.data[0] >> n;
  t1.maxDigit = t2.maxDigit = 1;
}

const BIGINT& solve()
{
  bi_add(t3, t1, t2);
  for (int i=2; i<n; ++i) {
    bi_mul(t3, t2, t2);
    bi_add(t3, t3, t1);
    t1 = move(t2);
    t2 = move(t3);
  }
  return t2;
}

int main (int argc, char* argv[])
{
  input();
  print(solve());

  return 0;
}

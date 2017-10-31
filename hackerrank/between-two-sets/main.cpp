#include <vector>
#include <iostream>

using namespace std;

int gcd(int a, int b)
{
  int remain;
  while (b != 0) {
    remain = b;
    b = a % b;
    a = remain;
  }
  return a;
}

int lcm(int a, int b)
{
  return a * b / gcd(a, b);
}

int getTotalX(vector <int> a, vector <int> b) {
    // Complete this function
    int size_a = a.size();
    int lcm_a = a[0];
    for (int i=1; i<size_a; ++i)
      lcm_a = lcm(lcm_a, a[i]);

    int size_b = b.size();
    int gcd_b = b[0];
    for (int i=1; i<size_b; ++i)
      gcd_b = gcd(gcd_b, b[i]);

    if (gcd_b % lcm_a != 0) return 0;

    int d = gcd_b / lcm_a;
    int comb = 1;
    for (int i=2; i<=d; i=(i==2 ? i+1 : i+2)) {
      int cnt = 0;
      while (d % i == 0) {
        ++cnt;
        d /= i;
      }
      comb *= (cnt+1);
    }

    return comb;
}

int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<int> a(n);
    for(int a_i = 0; a_i < n; a_i++){
       cin >> a[a_i];
    }
    vector<int> b(m);
    for(int b_i = 0; b_i < m; b_i++){
       cin >> b[b_i];
    }
    int total = getTotalX(a, b);
    cout << total << endl;
    return 0;
}

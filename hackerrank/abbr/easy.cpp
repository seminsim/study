#include <string>
#include <iostream>

using namespace std;

bool isMatch(string& a, string& b, int a_cur, int b_cur)
{
  if (a.length() - a_cur < b.length() - b_cur) return false;  // not possible length

  if (a_cur >= a.length() && b_cur >= b.length()) return true;  // exactly matched
  if (a_cur >= a.length()) return false;  // not possible matching tail part

  if (b_cur >= b.length()){ // all characters are matched
    int a_len = a.length();
    for (int i=a_cur; i<a_len; ++i){  // skip all lower cases
      if (a[i] < 'a') return false;
    }
    return true;
  }

  char c_a = a[a_cur];
  char c_b = b[b_cur];

  // skip unmatched lower cases
  while (c_a >= 'a' && (c_a-'a' + 'A') != c_b) c_a = a[++a_cur];

  if (c_a >= 'a') {
    // matched lower case. may or maynot contain
    return isMatch(a, b, a_cur+1, b_cur+1) || isMatch(a, b, a_cur+1, b_cur);
  }else{
    // capital (matched or failed)
    if (c_a != c_b) return false;
    return isMatch(a, b, a_cur+1, b_cur+1);
  }
}

string solve()
{
  string a, b;
  cin >> a >> b;

  return isMatch(a, b, 0, 0) ? "YES" : "NO";
}

int main (int argc, char* argv[])
{
  int N;
  cin >> N;
  for (int i=0; i<N; ++i)
    cout << solve() << endl;
  return 0;
}

#include <bits/stdc++.h>

using namespace std;

vector<bool> matched;

string richieRich(string s, int n, int k){
  int s_len = n;
  int l_max = (s_len+1) / 2;
  int center = -1;
  if (s_len % 2 == 1) center = s_len/2;

  matched.resize(l_max);
  int misMatchedCount = 0;
  bool isMatched;
  for (int i=0; i<l_max; ++i) {
    isMatched = s[i] == s[s_len-i-1];
    matched[i] = isMatched;
    if (!isMatched) misMatchedCount++;
  }

  // impossible to fix
  if (misMatchedCount > k) return "-1";

  // fix
  for (int i=0; i<l_max; ++i) {
    if (matched[i]) continue;
    int bigger;
    bigger = max(s[i], s[s_len-i-1]);
    s[i] = s[s_len-i-1] = bigger;
    k--;
  }

  // maximize
  for (int i=0; i<l_max && k>0; ++i) {
    if (i == center) {
      s[i] = '9';
      k--;
    } else if (matched[i]) {
      if (k < 2) continue;  // sufficient action
      if (s[i] == '9') continue;  // already max
      s[i] = s[s_len-i-1] = '9';
      k -= 2;
    } else {
      if (s[i] == '9') continue;  // already max
      s[i] = s[s_len-i-1] = '9';
      k--;
    }
  }

  return s.substr(0, s_len);
}

int main() {
  int n;
  cin >> n;
  int k;
  cin >> k;
  string s;
  cin >> s;
  string result = richieRich(s, n, k);
  cout << result << endl;
  return 0;
}

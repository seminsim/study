#include <bits/stdc++.h>

using namespace std;

map<char, int> freq;
map<int, int> freqCount;

const string strYes = "YES";
const string strNo = "NO";

string isValid(string s){
  // Complete this function
  int s_len = s.length();
  if (s_len == 0) return strYes;

  for (int i=0; i<s_len; ++i) {
    if (freq.find(s[i]) == freq.end()) freq[s[i]] = 1;
    else freq[s[i]] ++;
  }

  for (auto& f : freq)
    if (freqCount.find(f.second) == freqCount.end()) freqCount[f.second] = 1;
    else freqCount[f.second] ++;

  if (freqCount.size() == 1) return strYes;
  if (freqCount.size() > 2) return strNo;

  if (freqCount.find(1) != freqCount.end() && freqCount[1] == 1) return strYes;
  auto it = freqCount.begin();
  auto itSecond = freqCount.rbegin();
  if (itSecond->second == 1 && it->first+1 == itSecond->first) return strYes;
  return strNo;
}

int main() {
  string s;
  cin >> s;
  string result = isValid(s);
  cout << result << endl;
  return 0;
}

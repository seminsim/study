#include <iostream>
#include <string>
#include <vector>

using namespace std;

string longestCommonPrefix (vector<string>& strs)
{
  if (strs.size() == 0) return "";

  int strsSize = strs.size();
  int len = 0;
  len = strs[0].length();
  for (int i=1; i<strsSize; ++i) {
    if (strs[i].length() < len) len = strs[i].length();
  }

  for (int i=0; i<len; ++i) {
    char c = strs[0][i];
    for (int j=1; j<strsSize; ++j) {
      if (c != strs[j][i]) return strs[0].substr(0, i);
    }
  }

  return strs[0].substr(0, len);
}

int main (int argc, char* argv[])
{
  vector<string> strs(2);
  strs[0] = "aa";
  strs[1] = "a";

  cout << longestCommonPrefix(strs) << endl;
  return 0;
}

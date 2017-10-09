#include <iostream>

#define DEBUG 0
#define DebugOnly if(DEBUG)

using namespace std;

bool isMatch (string& s, string& p, int spos, int ppos)
{
  DebugOnly cout << "isMatch " << s << " " << p << " " << spos << " " << ppos << endl;
  if (spos == s.length() && ppos == p.length()) return true;
  if (ppos == p.length()) return false;

  if (ppos+1 == p.length()) {
    if (p[ppos] != '.' && s[spos] != p[ppos]) return false;
    return isMatch(s, p, spos+1, ppos+1);
  }

  if (p[ppos+1] == '*') {
    int skip = 0;
    char c;
    c = p[ppos];
    while (
      skip == 0 ||
      (
        (spos+skip) <= s.length() &&
        (c == '.' || c == s[spos+skip-1])
      )
    ) {
      if (isMatch(s, p, spos+skip, ppos+2)) return true;
      skip ++;
    }
    return false;
  } else {
    if (p[ppos] != '.' && s[spos] != p[ppos]) return false;
    return isMatch(s, p, spos+1, ppos+1);
  }
}

bool isMatch (string s, string p)
{
  return isMatch(s, p, 0, 0);
}

int main (int argc, char* argv[])
{
  cout << (isMatch(argv[1], argv[2]) ? "true" : "false") << endl;
  return 0;
}

#include <cstdlib>
#include <cstdio>

class Solution {
public:
    string countAndSay (string term)
    {
      string ret;
      int len = term.length();
      char c;
      char countStr[20];
      int count;

      c = term[0];
      count = 1;
      for (int i=1; i<len; ++i) {
        if (c == term[i]) {
          count++;
        } else {
          sprintf(countStr, "%d", count);
          ret = ret + countStr + c;

          c = term[i];
          count = 1;
        }
      }
      sprintf(countStr, "%d", count);
      ret = ret + countStr + c;

      return ret;
    }

    string countAndSay (int n)
    {
      string term = "1";
      for (int i=1; i<n; ++i) {
        term = countAndSay(term);
      }
      return term;
    }
};
class Solution {
public:
    int getPalindromicLength(string& s, int length, int pos)
    {
      int longest = 1;
      for (int i=1; i<=pos && i<length-pos; ++i) {
        if (s[pos-i] != s[pos+i]) break;
        longest += 2;
      }

      if (pos+1 == length || s[pos] != s[pos+1]) return longest;

      int longest2 = 2;
      for (int i=1; i<=pos && i<length-pos-1; ++i) {
        if (s[pos-i] != s[pos+i+1]) break;
        longest2 += 2;
      }

      return (longest > longest2) ? longest : longest2;
    }

    string solve (string s)
    {
      int len = s.length();
      int max = 0;
      int maxpos = 0;
      int cur;
      string maxSubStr;
      for (int i=0; i<len; ++i) {
        cur = getPalindromicLength(s, len, i);
        if (cur > max) {
          max = cur;
          maxpos = i;
        }
        if (max >= (1 + 2 * (len - i - 1))) break;
      }
      return s.substr(maxpos - ((max-1) / 2), max);
    }

    string longestPalindrome(string s) {
        return solve(s);
    }
};
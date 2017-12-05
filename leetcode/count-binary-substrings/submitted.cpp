class Solution {
public:
    int maxExpand(string& s, int i, int size, char cf, char cr)
    {
      int j=1;
      while ((i-1-j)>=0 && (i+j) < size) {
        if (s[i-1-j] != cf || s[i+j] != cr) break;
        ++j;
      }
      return j;
    }

    int countBinarySubstrings(string s) {
      int sum = 0;
      int size = s.length();
      for (int i=1; i<size; ++i) {
        if (s[i-1] == s[i]) continue;
        sum += maxExpand(s, i, size, s[i-1], s[i]);
      }
      return sum;
    }
};

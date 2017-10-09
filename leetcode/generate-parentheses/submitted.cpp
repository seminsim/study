class Solution {
public:
    vector<string> generateParenthesis (int n, int opened, string prefix)
    {
      vector<string> result;
      if (opened == 1 && n==1) {
        result.push_back (prefix + ")");
        return result;
      }

      if (n > 0 && opened < n) {
        vector<string> ret;
        ret = generateParenthesis(n, opened+1, prefix + "(");
        result.insert( result.end(), ret.begin(), ret.end() );
      }
      if (opened > 0) {
        vector<string> ret;
        ret = generateParenthesis(n-1, opened-1, prefix + ")");
        result.insert( result.end(), ret.begin(), ret.end() );
      }

      return result;
    }

    vector<string> generateParenthesis (int n)
    {
      return generateParenthesis(n, 0, "");
    }
};
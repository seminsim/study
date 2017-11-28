class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
      set<int> s;
      for (const auto& n : nums) {
        if (n > 0) s.insert(n);
      }
      int i = 1;
      const auto it_end = s.end();
      while(s.find(i) != it_end) ++i;
      return i;
    }
};
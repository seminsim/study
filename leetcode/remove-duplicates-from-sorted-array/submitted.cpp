class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
      int size = nums.size();
      if (size == 0) return 0;

      vector<bool> first(size, false);
      first[0] = true;
      for (int i=1; i<size; ++i) {
        first[i] = nums[i] > nums[i-1];
      }

      int cur = 0;
      for (int i=0; i<size; ++i) {
        if (first[i]) nums[cur++] = nums[i];
      }

      return cur;
    }
};
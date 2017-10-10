class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
      int size = nums.size();

      int min, max, mid, val;

      vector<int> ret(2);
      ret[0] = -1;
      ret[1] = -1;

      // search first matched
      min = 0;
      max = size;
      while (min < max) {
        mid = (min + max) / 2;
        val = nums[mid];
        if (val == target && (mid == 0 || nums[mid-1] < target)) {
          ret[0] = mid;
          break;
        }

        if (val >= target) max = mid;
        else min = mid + 1;
      }

      // not found
      if (ret[0] < 0) {
        return ret;
      }

      // search last matched
      min = 0;
      max = size;
      while (min < max) {
        mid = (min + max) / 2;
        val = nums[mid];
        if (val == target && (mid == size-1 || nums[mid+1] > target)) {
          ret[1] = mid;
          break;
        }

        if (val > target) max = mid;
        else min = mid + 1;
      }

      return ret;
    }
};
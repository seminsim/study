class Solution {
public:
    int search(vector<int>& nums, int target) {
      int size = nums.size();
      if (size == 0) return -1;

      int first = nums[0];

      if (target == first) return 0;

      if (target < first) {
        // exists on right side
        int min = 1;
        int max = size;
        int mid, val;
        while (min < max) {
          mid = (min + max) / 2;
          val = nums[mid];
          if (val == target) return mid;
          if (val > first || val < target) min = mid+1;
          else max = mid;
        }
        return -1;
      }

      if (target > first) {
        // exists on left side
        int min =1;
        int max = size;
        int mid, val;
        while (min < max) {
          mid = (min + max) / 2;
          val = nums[mid];
          if (val == target) return mid;
          if (val < first || val > target) max = mid;
          else min = mid+1;
        }
        return -1;
      }
    }
};
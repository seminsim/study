class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
      map<int, int> ms;
      int sum = 0;
      int matched = 0;
      int size = nums.size();
      for (int i=0; i<size; ++i) {
        sum += nums[i];
        if (ms.find(sum) == ms.end()) {
          ms[sum] = 1;
        } else {
          ms[sum]++;
        }
      }

      sum = 0;
      for (int i=0; i<size; ++i) {
        if (ms.find(k+sum) != ms.end()) {
          matched += ms[k+sum];
        }
        sum += nums[i];
        if (ms[sum] == 1) {
          ms.erase(sum);
        } else {
          ms[sum]--;
        }
      }

      return matched;
    }
};
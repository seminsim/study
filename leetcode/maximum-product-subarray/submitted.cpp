class Solution {
public:
    int maxProduct(vector<int>& nums) {
      vector<int> sub_nums;
      int max_product = numeric_limits<int>::min();
      for (const auto& num : nums) {
        if (num != 0) {
          sub_nums.push_back(num);
        } else {
          max_product = max(max_product, 0);
          if (!sub_nums.empty()) {
            max_product = max(max_product, subMaxProduct(sub_nums));
            sub_nums.clear();
          }
        }
      }
      if (!sub_nums.empty()) {
        max_product = max(max_product, subMaxProduct(sub_nums));
        sub_nums.clear();
      }
      return max_product;
    }

    int subMaxProduct(vector<int>& nums) {
      int size = nums.size();

      if (size == 1) return nums[0];

      bool is_even = true;
      int first = -1;
      int last = -1;
      for (int i=0; i<size; ++i){
        if (nums[i] < 0) {
          if (first < 0) first = i;
          last = i;
          is_even = !is_even;
        }
      }

      int res = 1, res_r = 1;
      if (is_even) {
        for (const auto& num : nums) res *= num;
        return res;
      } else {
        for (int i=0; i<last; ++i) res *= nums[i];
        for (int i=first+1; i<size; ++i) res_r *= nums[i];
        return max(res, res_r);
      }
    }
};

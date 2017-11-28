class Solution {
public:
    void permuteSub(
      vector<vector<int>>& res,
      const vector<int>& nums,
      vector<bool>& selected,
      vector<int>& current,
      int remaining )
    {
      if (remaining == 0) {
        res.push_back(current);
        return;
      }
      int size = nums.size();
      for (int i=0; i<size; ++i) {
        if (selected[i]) continue;
        selected[i] = true;
        current[size-remaining] = nums[i];
        permuteSub(res, nums, selected, current, remaining-1);
        selected[i] = false;
      }
    }

    vector<vector<int>> permute(vector<int>& nums) {
      vector<vector<int>> res;
      vector<bool> selected(nums.size(), false);
      vector<int> current(nums.size());
      permuteSub(res, nums, selected, current, nums.size());
      return res;
    }
};
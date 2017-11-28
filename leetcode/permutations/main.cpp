#include <iostream>
#include <vector>

using namespace std;

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

void input(vector<int>& i)
{
  i.resize(3);
  i[0] = 1;
  i[1] = 2;
  i[2] = 3;
}

int main (int argc, char* argv[])
{
  vector<int> i;
  input(i);
  Solution s;
  vector<vector<int>> res = s.permute(i);
  for (const auto& x : res) {
    for (const auto& y : x) {
      cout << y;
    }
    cout << endl;
  }
}

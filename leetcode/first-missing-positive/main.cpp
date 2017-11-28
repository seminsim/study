#include <iostream>
#include <vector>
#include <set>

using namespace std;

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

void input(vector<int>& nums)
{
  nums.resize(4);
  nums[0] = 3;
  nums[1] = 4;
  nums[2] = -1;
  nums[3] = 1;
}

int main(int argc, char* argv[])
{
  vector<int> nums;
  input(nums);
  Solution s;
  cout << s.firstMissingPositive(nums) << endl;

  return 0;
}

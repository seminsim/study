#include <iostream>
#include <vector>
#include <map>

using namespace std;


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

int main (int argc, char* argv[])
{
  vector<int> nums = {-1, -1, 1}; int k = 0;
  // vector<int> nums = {-1, -1, 2}; int k = 1;

  Solution s;
  cout << s.subarraySum(nums, k) << endl;

  return 0;
}

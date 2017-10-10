#include <vector>

#include <iostream>

using namespace std;

vector<int> searchRange (vector<int>& nums, int target)
{
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

void generateInput (vector<int>& nums, int& target)
{
  nums.clear();
  nums.push_back(5);
  nums.push_back(7);
  nums.push_back(7);
  nums.push_back(8);
  nums.push_back(8);
  nums.push_back(10);

  target = 10;
}

int main (int argc, char* argv[])
{
  vector<int> nums;
  int target;

  generateInput(nums, target);

  vector<int> result;
  result = searchRange(nums, target);
  cout << result[0] << " " << result[1] << endl;

  return 0;
}

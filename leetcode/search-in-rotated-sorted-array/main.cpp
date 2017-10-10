#include <vector>

#include <iostream>

using namespace std;

int search (vector<int>& nums, int target)
{
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

void generateInput (vector<int>& nums, int& target)
{
  nums.clear();
  nums.push_back(4);
  nums.push_back(5);
  nums.push_back(6);
  nums.push_back(7);
  nums.push_back(0);
  nums.push_back(1);
  nums.push_back(2);

  target = 5;
}

int main (int argc, char* argv[])
{
  vector<int> nums;
  int target;

  generateInput(nums, target);
  cout << search(nums, target) << endl;

  return 0;
}

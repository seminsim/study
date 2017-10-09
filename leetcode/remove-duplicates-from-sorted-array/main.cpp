#include <vector>

#include <iostream>

using namespace std;

int removeDuplicates (vector<int>& nums)
{
  int size = nums.size();
  if (size == 0) return 0;

  vector<bool> first(size, false);
  first[0] = true;
  for (int i=1; i<size; ++i) {
    first[i] = nums[i] > nums[i-1];
  }

  int cur = 0;
  for (int i=0; i<size; ++i) {
    if (first[i]) nums[cur++] = nums[i];
  }

  return cur;
}

void generateInput (vector<int>& nums)
{
  nums.clear();
  nums.push_back(1);
  nums.push_back(1);
  nums.push_back(2);
}

void printNums (vector<int>& nums)
{
  int size = nums.size();
  for (int i=0; i<size; ++i) {
    cout << nums[i] <<  " ";
  }
  cout << endl;
}

int main (int argc, char* argv[])
{
  vector<int> nums;
  generateInput(nums);
  printNums(nums);
  cout << removeDuplicates(nums) << endl;
  printNums(nums);

  return 0;
}

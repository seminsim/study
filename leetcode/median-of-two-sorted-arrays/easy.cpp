#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


void printVector(vector<int>& nums, string name = string("NONAME"))
{
  cout << name << ": ";
  for (auto it = nums.begin(); it != nums.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

void buildInputEx1(vector<int>& nums1, vector<int>& nums2)
{
  nums1.resize(2);
  nums1[0] = 1;
  nums1[1] = 3;

  nums2.resize(1);
  nums2[0] = 2;
}

void buildInputEx2(vector<int>& nums1, vector<int>& nums2)
{
  nums1.resize(2);
  nums1[0] = 1;
  nums1[1] = 2;

  nums2.resize(2);
  nums2[0] = 3;
  nums2[1] = 4;
}

void buildInputRandom(vector<int>& nums1, vector<int>& nums2, int seed)
{
  srand(seed);

  int size1 = rand() % 10 + 10;
  nums1.resize(size1);
  for (int i=0; i<size1; ++i) {
    nums1[i] = rand() % 100;
  }
  sort(nums1.begin(), nums1.end());

  int size2 = rand() % 10 + 10;
  nums2.resize(size2);
  for (int i=0; i<size2; ++i) {
    nums2[i] = rand() % 100;
  }
  sort(nums2.begin(), nums2.end());
}

double solve(vector<int>& nums1, vector<int>& nums2)
{
  int nums1size = nums1.size();
  int nums2size = nums2.size();
  int mergedSize = nums1size + nums2size;

  vector<int> merged(mergedSize);

  for (int i=0; i<nums1size; ++i) {
    merged[i] = nums1[i];
  }

  for (int i=0; i<nums2size; ++i) {
    merged[nums1size + i] = nums2[i];
  }

  sort(merged.begin(), merged.end());

  if (mergedSize % 2 == 0) {
    return (
        merged[(mergedSize / 2) - 1] +
        merged[(mergedSize / 2)]
      ) / 2.0;
  } else {
    return merged[(mergedSize / 2)];
  }
}

int main(int argc, char* argv[])
{
  vector<int> nums1;
  vector<int> nums2;

  buildInputRandom(nums1, nums2, atoi(argv[1]));
  cout << solve(nums1, nums2) << endl;

  return 0;
}

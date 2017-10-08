#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>

using namespace std;


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

void buildInputEx3(vector<int>& nums1, vector<int>& nums2)
{
  nums1.resize(0);

  nums2.resize(1);
  nums2[0] = 1;
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

map<int, int> lbOffsetCache;
int lbOffset(vector<int>& nums2, int needle)
{
  // check cached
  auto it_cached = lbOffsetCache.find(needle);
  if (it_cached != lbOffsetCache.end()) { return it_cached->second; }

  // at boundary
  int size = nums2.size();

  if (needle > nums2[size-1]) { return size; }
  if (needle <= nums2[0]) { return 0; }

  int min = 0;
  int max = size;
  int cur;
  while (true) {
    cur = (min + max) / 2;
    if (needle > nums2[cur] && needle <= nums2[cur+1]) {
      // cache
      lbOffsetCache[needle] = cur + 1;
      return cur + 1;
    }
    if (needle <= nums2[cur]) {
      max = cur;
    } else {
      min = cur + 1;
    }
  }


}

map<int, int> ubOffsetCache;
int ubOffset(vector<int>& nums1, int needle)
{
  // check cached
  auto it_cached = ubOffsetCache.find(needle);
  if (it_cached != ubOffsetCache.end()) { return it_cached->second; }

  // at boundary
  int size = nums1.size();

  if (needle >= nums1[size-1]) { return size; }
  if (needle < nums1[0]) { return 0; }

  // binary search
  int min = 0;
  int max = size;
  int cur;
  while (true) {
    cur = (min + max) / 2;
    if (needle >= nums1[cur] && needle < nums1[cur+1]) {
      // cache
      ubOffsetCache[needle] = cur + 1;
      return cur + 1;
    }
    if (needle < nums1[cur]) {
      max = cur;
    } else {
      min = cur + 1;
    }
  }
}

int getNum1Index(vector<int>& nums1, vector<int>& nums2, int idx)
{
  return idx + lbOffset(nums2, nums1[idx]);
}

int getNum2Index(vector<int>& nums1, vector<int>& nums2, int idx)
{
  return idx + ubOffset(nums1, nums2[idx]);
}

void offsetTest(vector<int>& nums1, vector<int>& nums2)
{
  int size1 = nums1.size();
  int size2 = nums2.size();

  // print values
  cout << "NUMS1: ";
  for (int i=0; i<size1; ++i) {
    cout << nums1[i] << " ";
  }
  cout << endl;

  cout << "NUMS2: ";
  for (int i=0; i<size2; ++i) {
    cout << nums2[i] << " ";
  }
  cout << endl;

  // print offsets
  cout << "NUMS1 Offsets: ";
  for (int i=0; i<size1; ++i) {
    cout << (i + lbOffset(nums2, nums1[i])) << " ";
  }
  cout << endl;

  cout << "NUMS1 Offsets: ";
  for (int i=0; i<size2; ++i) {
    cout << (i + ubOffset(nums1, nums2[i])) << " ";
  }
  cout << endl;
}

int find(vector<int>& nums1, vector<int>& nums2, int targetIdx)
{
  int size1 = nums1.size();
  int size2 = nums2.size();

  // binary search on nums1
  {
    int min = 0;
    int max = size1;
    int cur;
    int curIndex;
    while (min < max) {
      cur = (min + max) / 2;
      curIndex = getNum1Index(nums1, nums2, cur);
      if (curIndex == targetIdx) { return nums1[cur]; }
      if (curIndex < targetIdx) { min = cur + 1; }
      else { max = cur; }
    }
  }

  // binary search on nums2
  {
    int min = 0;
    int max = size2;
    int cur;
    int curIndex;
    while (min < max) {
      cur = (min + max) / 2;
      curIndex = getNum2Index(nums1, nums2, cur);
      if (curIndex == targetIdx) { return nums2[cur]; }
      if (curIndex < targetIdx) { min = cur + 1; }
      else { max = cur; }
    }
  }

  cout << "ERROR!!!" << endl;
}

double solve(vector<int>& nums1, vector<int>& nums2)
{
  int size1 = nums1.size();
  int size2 = nums2.size();

  if (size1 == 0) {
    if (size2 % 2 == 0) {
      return (nums2[size2 / 2] + nums2[(size2 / 2) - 1]) / 2.0;
    } else {
      return nums2[size2 / 2];
    }
  }

  if (size2 == 0) {
    if (size1 % 2 == 0) {
      return (nums1[size1 / 2] + nums1[(size1 / 2) - 1]) / 2.0;
    } else {
      return nums1[size1 / 2];
    }
  }

  int l = nums1.size() + nums2.size();
  if (l % 2 == 0) {
    return (find(nums1, nums2, l/2) + find(nums1, nums2, (l/2) - 1)) / 2.0;
  } else {
    return find(nums1, nums2, l/2);
  }
}

int main(int argc, char* argv[])
{
  vector<int> nums1;
  vector<int> nums2;

  // buildInputEx3(nums1, nums2);
  // cout << solve(nums1, nums2) << endl;

  buildInputRandom(nums1, nums2, atoi(argv[1]));
  cout << solve(nums1, nums2) << endl;

  return 0;
}
